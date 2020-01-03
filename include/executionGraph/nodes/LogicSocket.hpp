//! ========================================================================================
//!  ExecutionGraph
//!  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//!
//!  @date Mon Jan 08 2018
//!  @author Gabriel Nützi, <gnuetzi (at) gmail (døt) com>
//!
//!  This Source Code Form is subject to the terms of the Mozilla Public
//!  License, v. 2.0. If a copy of the MPL was not distributed with this
//!  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//! ========================================================================================

#pragma once

#include <unordered_set>
#include <vector>
#include <meta/meta.hpp>
#include <rttr/type>

#include "executionGraph/common/Assert.hpp"
#include "executionGraph/common/ConstExprAlgos.hpp"
#include "executionGraph/common/DemangleTypes.hpp"
#include "executionGraph/common/EnumClassHelper.hpp"
#include "executionGraph/common/TupleUtil.hpp"
#include "executionGraph/common/TypeDefs.hpp"
#include "executionGraph/nodes/LogicCommon.hpp"
#include "executionGraph/nodes/LogicNode.hpp"
#include "executionGraph/nodes/LogicSocketDescription.hpp"

namespace executionGraph
{
    //! The socket base class.
    class LogicSocketBase
    {
    public:
        EG_DEFINE_TYPES();

        LogicSocketBase(LogicSocketBase&&) = default;
        LogicSocketBase& operator=(LogicSocketBase&&) = default;

    protected:
        LogicSocketBase(rttr::type type,
                        SocketIndex index,
                        const LogicNode& parent) noexcept
            : m_type(type)
            , m_index(index)
            , m_parent(&parent)
        {
        }

    public:
        inline SocketIndex getIndex() const noexcept { return m_index; }
        inline const rttr::type& type() const noexcept { return m_type; }

        inline const LogicNode& parent() const noexcept { return *m_parent; }

        template<typename T>
        bool isType() const noexcept
        {
            return type() == rttr::type::get<T>();
        }

    protected:
        rttr::type m_type;                    //!< The type of this socket.
        SocketIndex m_index;                  //!< The index of the slot at which this socket is installed in a LogicNode.
        const LogicNode* m_parent = nullptr;  //!< The parent node of of this socket.
    };

    //! The input socket base class.
    class LogicSocketInputBase : public LogicSocketBase
    {
    public:
        EG_DEFINE_TYPES();

    protected:
        template<typename... Args>
        LogicSocketInputBase(Args&&... args) noexcept
            : LogicSocketBase(std::forward<Args>(args)...)
        {
        }

        ~LogicSocketInputBase() noexcept = default;

    public:
        //! Cast to a logic socket of type `LogicSocketInput<T>*`.
        //! The cast fails at runtime if the data type `T` does not match!
        template<typename T>
        auto& castToType() const noexcept
        {
            EG_LOGTHROW_IF(!this->template isType<T>(),
                           "Casting socket index '{0}' with type index '{1}' into type"
                           "'{2}' of node id: '{3}' which is wrong!",
                           this->getIndex(),
                           this->type(),
                           rttr::type::get<T>().get_name(),
                           this->parent().getId());

            return static_cast<const LogicSocketInput<T>&>(*this);
        }

        //! Non-const overload.
        template<typename T>
        auto& castToType() noexcept(!throwIfBadSocketCast)
        {
            return const_cast<LogicSocketInput<T>&>(static_cast<LogicSocketInputBase const*>(this)->castToType<T>());
        }

    public:
        static constexpr bool isInput() { return true; }
        static constexpr bool isOutput() { return false; }
    };

    //! The output socket base class.
    class LogicSocketOutputBase : public LogicSocketBase
    {
    public:
        EG_DEFINE_TYPES();

    protected:
        template<typename... Args>
        LogicSocketOutputBase(Args&&... args)
            : LogicSocketBase(std::forward<Args>(args)...)
        {
        }

        ~LogicSocketOutputBase() noexcept = default;

        LogicSocketOutputBase(LogicSocketOutputBase&&) = default;
        LogicSocketOutputBase& operator=(LogicSocketOutputBase&&) = default;

    public:
        //! Cast to a logic socket of type `LogicSocketOutput`<T>*.
        //! The cast fails at runtime if the data type `T` does not match!
        template<typename T>
        auto& castToType() const noexcept
        {
            if constexpr(throwIfBadSocketCast)
            {
                EG_LOGTHROW_IF(this->m_type != rttr::type::get<T>(),
                               "Casting socket index '{0}' with type index '{1}' into "
                               "'{2}' of node id: '{3}' which is wrong!",
                               this->getIndex(),
                               this->type(),
                               rttr::type::get<T>().get_name(),
                               this->parent().getId());
            }

            return static_cast<const LogicSocketOutput<T>&>(*this);
        }

        //! Non-const overload.
        template<typename T>
        auto* castToType()
        {
            return const_cast<LogicSocketOutput<T>&>(static_cast<LogicSocketOutputBase const*>(this)->castToType<T>());
        }

    public:
        static constexpr bool isInput() { return false; }
        static constexpr bool isOutput() { return true; }
    };

    template<typename TTraits, typename Derived>
    class LogicSocketConnections
    {
    public:
        using NodeData            = typename TTraits::NodeDataConnections;
        using NodeDataConnections = typename TTraits::NodeDataConnections;
        static_assert(std::is_base_of_v<NodeDataConnections, NodeData>,
                      "NodeDataConnections needs to be a base of NodeData");

        friend NodeDataConnections;

    protected:
        LogicSocketConnections() = default;

    public:
        ~LogicSocketConnections()
        {
            disconnect();
        }

    public:
        //! Connect a data node.
        void connect(NodeDataConnections& nodeData) noexcept
        {
            disconnect();
            onConnect(nodeData);
            m_nodeData->onConnect(static_cast<Derived&>(*this));
        }

        //! Disconnect the data node.
        void disconnect() noexcept
        {
            if(m_nodeData)
            {
                m_nodeData->onDisconnect(static_cast<Derived&>(*this));
                onDisconnect();
            }
        }

        NodeData* dataNode() { return m_nodeData; }

    protected:
        void onConnect(const NodeData& nodeData) noexcept
        {
            m_nodeData = const_cast<NodeData*>(&nodeData);
        }

        void onDisconnect() noexcept
        {
            m_nodeData = nullptr;
        }

    private:
        NodeData* m_nodeData = nullptr;  //! Connected data node.
    };

    /* ---------------------------------------------------------------------------------------*/
    /*!
        The input socket.

        @date Sat Dec 28 2019
        @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
    */
    /* ---------------------------------------------------------------------------------------*/
    template<typename TData>
    class LogicSocketInput final : public LogicSocketInputBase,
                                   public ConnectionTraits<TData>::InputSocketConnections
    {
    public:
        EG_DEFINE_TYPES();
        using Data = TData;

    public:
        template<typename... Args>
        LogicSocketInput(Args&&... args)
            : LogicSocketInputBase(rttr::type::get<Data>(), std::forward<Args>(args)...)
        {
        }

        ~LogicSocketInput() noexcept = default;

        //! Copy not allowed (since parent pointer)
        LogicSocketInput(const LogicSocketInput& other) = delete;
        LogicSocketInput& operator=(const LogicSocketInput& other) = delete;

        //! Move allowed
        LogicSocketInput(LogicSocketInput&& other) = default;
        LogicSocketInput& operator=(LogicSocketInput&& other) = default;
    };

    /* ---------------------------------------------------------------------------------------*/
    /*
        The output socket.

        @date Sat Dec 28 2019
        @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
    */
    /* ---------------------------------------------------------------------------------------*/
    template<typename TData>
    class LogicSocketOutput final : public LogicSocketOutputBase,
                                    public ConnectionTraits<TData>::OutputSocketConnections
    {
    public:
        EG_DEFINE_TYPES();
        using Data = TData;

    public:
        template<typename... Args>
        LogicSocketOutput(Args&&... args)
            : LogicSocketOutputBase(rttr::type::get<Data>(), std::forward<Args>(args)...)
        {
        }

        ~LogicSocketOutput() noexcept = default;

        //! Copy not allowed (since parent pointer)
        LogicSocketOutput(const LogicSocketOutput& other) = delete;
        LogicSocketOutput& operator=(const LogicSocketOutput& other) = delete;

        //! Move allowed
        LogicSocketOutput(LogicSocketOutput&& other) = default;
        LogicSocketOutput& operator=(LogicSocketOutput&& other) = default;
    };

    //! Make a container for input socket from `LogicSocketDescription`s.
    //! @return A `std::tuple` of `LogicSocket<...>`.
    template<auto& descs,
             typename Node,
             EG_ENABLE_IF((meta::is<naked<decltype(descs)>, std::tuple>::value) &&
                          std::is_constant_evaluated())>
    auto makeSockets(const Node& node)
    {
        []<typename... Descs>(std::tuple<Descs...>)
        {
            static_assert(isInputDescriptions<Descs...> ||
                              isOutputDescriptions<Descs...>,
                          "Either all inputs or outputs!");
            static_assert(belongSocketDescriptionsToSameNodes<Descs...>,
                          "You cannot mix descriptions for different nodes!");
        }
        (descs);

        return tupleUtil::invoke(
            descs,
            [&](auto&&... ds) {
                std::array indices = {ds.index()...};
                static_assert(cx::is_sorted(indices.begin(), indices.end()),
                              "All socket description need to be sorted!");
                return std::make_tuple(
                    typename naked<decltype(ds)>::SocketType(ds.index(), node)...);
            });
    }

    //! The container type for input sockets used in specific node implementation.
    //! A `std::tuple` of `LogicSocket<...>`.
    template<auto& inputDescs>
    using InputSocketsTuple = decltype(makeSockets<inputDescs>(std::declval<LogicNode>()));

    //! The container type for output sockets used in specific node implementation.
    //! A `std::tuple` of `LogicSocket<...>`.
    template<auto& outputDescs>
    using OutputSocketsTuple = decltype(makeSockets<outputDescs>(std::declval<LogicNode>()));

    //! Convert a tuple of sockets into a container `Container`
    //! of pointers pointing to the passed sockets.
    //! Used to registers sockets
    template<typename Container, typename... Type>
    auto makePtrList(std::tuple<Type...>& sockets)
    {
        using Pointer = typename Container::value_type;
        static_assert(std::is_pointer_v<Pointer>,
                      "Value type needs to be pointer");
        return tupleUtil::invoke(
            sockets,
            [](auto&... socket) {
                return Container{Pointer{&socket}...};
            });
    }

    //! Get an input socket of a tuple-like socket-container
    //! from a socket description `LogicSocketDescription`
    template<typename Sockets,
             typename SocketDesc,
             EG_ENABLE_IF((meta::is_v<Sockets, std::tuple> &&
                           isInputDescriptions<SocketDesc>))>
    auto& getInputSocket(Sockets& sockets, const SocketDesc&)
    {
        return std::get<SocketDesc::index()>(sockets);
    }

    //! Get an output socket of a tuple-like socket-container
    //! from a socket description `LogicSocketDescription`
    template<typename Sockets,
             typename SocketDesc,
             EG_ENABLE_IF((meta::is_v<Sockets, std::tuple> &&
                           isOutputDescriptions<SocketDesc>))>
    auto& getOutputSocket(Sockets& sockets, const SocketDesc&)
    {
        return std::get<SocketDesc::index()>(sockets);
    }

#define EG_DEFINE_SOCKET_GETTERS(Node, inputSockets, outputSockets)      \
    template<typename SocketDesc,                                        \
             EG_ENABLE_IF((isInputDescriptions<SocketDesc> &&            \
                           SocketDesc::template belongsToNode<Node>()))> \
    auto& socket(const SocketDesc& desc)                                 \
    {                                                                    \
        return executionGraph::getInputSocket(inputSockets, desc);       \
    }                                                                    \
    template<typename SocketDesc,                                        \
             EG_ENABLE_IF((isOutputDescriptions<SocketDesc> &&           \
                           SocketDesc::template belongsToNode<Node>()))> \
    auto& socket(const SocketDesc& desc)                                 \
    {                                                                    \
        return executionGraph::getOutputSocket(outputSockets, desc);     \
    }                                                                    \
    using __FILE__##__LINE__##FORCE_SEMICOLON = int

}  // namespace executionGraph