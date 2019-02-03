//! ========================================================================================
//!  ExecutionGraph
//!  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//!
//!  @date Sun Jan 14 2018
//!  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//!
//!  This Source Code Form is subject to the terms of the Mozilla Public
//!  License, v. 2.0. If a copy of the MPL was not distributed with this
//!  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//! ========================================================================================

#pragma once

#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <string>
#include <variant>
#include <vector>
#include <meta/meta.hpp>
#include <rttr/type>
#include <executionGraph/common/Deferred.hpp>
#include <executionGraph/common/Identifier.hpp>
#include <executionGraph/common/Synchronized.hpp>
#include <executionGraph/graphs/CycleDescription.hpp>
#include <executionGraph/graphs/ExecutionTree.hpp>
#include <executionGraph/serialization/GraphTypeDescription.hpp>
#include "executionGraph/common/FileSystem.hpp"
#include "executionGraphGui/backend/Backend.hpp"
#include "executionGraphGui/backend/ExecutionGraphBackendDefs.hpp"
#include "executionGraphGui/common/BinaryBufferView.hpp"
#include "executionGraphGui/common/RequestError.hpp"

/* ---------------------------------------------------------------------------------------*/
/*!
    The execution graph backend.

    @date Sun Feb 18 2018
    @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
 */
/* ---------------------------------------------------------------------------------------*/
class ExecutionGraphBackend final : public Backend
{
    RTTR_ENABLE()

public:
    using Id                   = executionGraph::Id;
    using IdNamed              = executionGraph::IdNamed;
    using GraphTypeDescription = executionGraph::GraphTypeDescription;
    using NodeId               = executionGraph::NodeId;
    using SocketIndex          = executionGraph::SocketIndex;
    using Deferred             = executionGraph::Deferred;

    template<typename... Args>
    using Synchronized = executionGraph::Synchronized<Args...>;

    template<typename K, typename T>
    using SyncedUMap = Synchronized<std::unordered_map<K, T>>;

    //! All supported graphs.
    using GraphConfigs                       = meta::list<executionGraph::GeneralConfig<>>;
    static constexpr std::size_t nGraphTypes = meta::size<GraphConfigs>::value;

    //! Traits details.
    struct details
    {
        // Get the graph from the backend.
        template<typename Config>
        using getGraph = typename ExecutionGraphBackendDefs<Config>::Graph;

        // List of graphs types.
        using Graphs = meta::transform<GraphConfigs, meta::quote<details::getGraph>>;

        // The underlying variant.
        template<typename Graph>
        using toPointer    = std::shared_ptr<Synchronized<Graph>>;
        using GraphVariant = meta::apply<meta::quote<std::variant>, meta::transform<Graphs, meta::quote<toPointer>>>;
    };

    using GraphVariant = details::GraphVariant;
    using Graphs       = details::Graphs;

private:
    class GraphStatus;

public:
    ExecutionGraphBackend(std::path rootPath)
        : Backend(IdNamed("ExecutionGraphBackend")), m_rootPath(rootPath) {}
    ~ExecutionGraphBackend() override = default;

    //! Load/Save graphs.
    //@{
    void saveGraph(const Id& graphId,
                   std::path filePath,
                   bool overwrite,
                   BinaryBufferView visualization = {});

    template<typename ResponseCreator>
    void loadGraph(const std::path& filePath,
                   ResponseCreator&& responseCreator);
    //@}

    //! Adding/removing graphs.
    //@{
    Id addGraph(const Id& graphType);
    void removeGraph(const Id& graphId);
    void removeGraphs();
    //@}

    //! Adding/removing nodes.
    //@{
    template<typename ResponseCreator>
    void addNode(const Id& graphId, std::string_view type, ResponseCreator&& responseCreator);

    void removeNode(const Id& graphId, NodeId id);
    //@}

    //! Adding/removing connections.
    //@{
    template<typename ResponseCreator>
    void addConnection(const Id& graphId,
                       NodeId outNodeId,
                       SocketIndex outSocketIdx,
                       NodeId inNodeId,
                       SocketIndex inSocketIdx,
                       bool isWriteLink,
                       bool checkForCycles,
                       ResponseCreator&& responseCreator);

    void removeConnection(const Id& graphId,
                          NodeId outNodeId,
                          SocketIndex outSocketIdx,
                          NodeId inNodeId,
                          SocketIndex inSocketIdx,
                          bool isWriteLink);
    //@}

    //! Information about graphs.
    //@{
public:
    //! Get all graph descriptions identified by its id.
    const std::unordered_map<Id, GraphTypeDescription>& getGraphTypeDescriptions() const;
    //@}

private:
    [[nodiscard]] executionGraph::Deferred initRequest(Id graphId);
    void clearGraphData(Id graphId);
    GraphVariant getGraph(const Id& graphId);

private:
    SyncedUMap<Id, GraphVariant> m_graphs;                  //! Graphs identified by its id.
    SyncedUMap<Id, std::shared_ptr<GraphStatus>> m_status;  //! Graph status for each graph id.
    // SyncedUMap<Id, std::shared_ptr<IGraphIExecutor> > m_executor; //!< Graph executors for each
    // graph id.

    const std::path m_rootPath;  //!< Root path where relative file paths are based on (save/load).
};

//! Add a node with type `type` to the graph with id `graphId`.
template<typename ResponseCreator>
void ExecutionGraphBackend::addNode(const Id& graphId,
                                    std::string_view type,
                                    ResponseCreator&& responseCreator)
{
    auto deferred = initRequest(graphId);

    GraphVariant graphVar = getGraph(graphId);

    // Remark: Here somebody could potentially call `removeGraph` (other thread)
    // which waits till all requests on this graph are handled.

    // Make a visitor to dispatch the "add" over the variant...
    auto add = [&](auto& graph) {
        using GraphType    = typename std::remove_cv_t<std::remove_reference_t<decltype(*graph)>>::DataType;
        using Config       = typename GraphType::Config;
        using NodeBaseType = typename Config::NodeBaseType;

        // Locking start
        auto graphL = graph->wlock();

        // Construct the node with the serializer
        typename ExecutionGraphBackendDefs<Config>::NodeSerializer serializer;
        NodeId id          = graphL->generateNodeId();
        NodeBaseType* node = nullptr;

        try
        {
            auto n = serializer.read(type, id);
            node   = graphL->addNode(std::move(n));
        }
        catch(executionGraph::Exception& e)
        {
            EXECGRAPHGUI_THROW_BAD_REQUEST(
                "Construction of node with type: '{0}' "
                "for graph id '{1}' failed: '{2}'",
                type,
                graphId.toString(),
                e.what());
        }

        EXECGRAPH_ASSERT(node != nullptr, "Node is nullptr!!?");

        // Create the response (with the graph locked)
        responseCreator(*graphL, *node);

        // Locking end
    };

    std::visit(add, graphVar);
}

//! Add a connection to the graph with id `graphId`.
template<typename ResponseCreator>
void ExecutionGraphBackend::addConnection(const Id& graphId,
                                          NodeId outNodeId,
                                          SocketIndex outSocketIdx,
                                          NodeId inNodeId,
                                          SocketIndex inSocketIdx,
                                          bool isWriteLink,
                                          bool checkForCycles,
                                          ResponseCreator&& responseCreator)
{
    auto deferred = initRequest(graphId);

    GraphVariant graphVar = getGraph(graphId);

    // Remark: Here somebody could potentially call `removeGraph` (other thread)
    // which waits till all requests on this graph are handled.

    // Make a visitor to dispatch the "add" over the variant...
    auto add = [&](auto& graph) {
        using GraphType = typename std::remove_cv_t<std::remove_reference_t<decltype(*graph)>>::DataType;

        // Potential cycles data structure
        std::vector<executionGraph::CycleDescription> cycles;

        // Locking start
        auto graphL = graph->wlock();
        try
        {
            EXECGRAPHGUI_THROW_BAD_REQUEST_IF(checkForCycles, "Checking cycles not yet implemented!");

            if(isWriteLink)
            {
                graphL->addWriteLink(outNodeId, outSocketIdx, inNodeId, inSocketIdx);
            }
            else
            {
                graphL->setGetLink(outNodeId, outSocketIdx, inNodeId, inSocketIdx);
            }
        }
        catch(executionGraph::Exception& e)
        {
            EXECGRAPHGUI_THROW_BAD_REQUEST(
                std::string("Adding connection from output node id '{0}' [socket idx: '{1}'] ") +
                    (isWriteLink ? "<-- " : "--> ") + "input node id '{2}' [socket idx: '{3}' not successful!",
                outNodeId,
                outSocketIdx,
                inNodeId,
                inSocketIdx);
        }

        // Create the response (with the graph locked)
        responseCreator(*graphL, std::move(cycles));

        // Locking end
    };

    std::visit(add, graphVar);
}

template<typename ResponseCreator>
void loadGraph(const std::path& filePath,
               ResponseCreator&& responseCreator)
{
    GraphVariant graphVar = getGraph(graphId);

    auto load = [&](auto graph) {
        using GraphType = typename std::decay_t<decltype(*graph)>::DataType;
        using Config    = typename GraphType::Config;

        typename ExecutionGraphBackendDefs<Config>::NodeSerializer nodeS;
        typename ExecutionGraphBackendDefs<Config>::GraphSerializer graphS(nodeS);

        auto graphgraphS.read(filePath);

        graph->withRLock([&](auto& graph) { graphS.write(graph,
                                                         descIt->second,
                                                         filePath,
                                                         overwrite,
                                                         visualization); });
    };

    std::visit(remove, graphVar);
}