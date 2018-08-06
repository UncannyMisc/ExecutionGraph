// =========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//
//  @date Tue May 01 2018
//  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// =========================================================================================

#ifndef executionGraph_serializer_LogicNodeSerializer_hpp
#define executionGraph_serializer_LogicNodeSerializer_hpp

#include <meta/meta.hpp>
#include "executionGraph/common/Factory.hpp"
#include "executionGraph/serialization/schemas/LogicNode_generated.h"

namespace executionGraph
{
    namespace serialization
    {
        /* ---------------------------------------------------------------------------------------*/
        /*!
            Serializer which loads a Logic Node.
            `NodeSerializerList` contains a type `Writer` and a type `Reader` which 
            both need to fullfill the requirements for `Type` in 
            `executionGrpah::StaticFactory<meta::list<Type,...>>`:

            The `Reader` contains the following interface:
            @code
                static std::unique_ptr<NodeBaseType>
                create(const serialization::LogicNode& node)
            @endcode

            The `Writer` contains Creators with the following interface:
            @code
                static std::pair<const uint8_t*, std::size_t>
                create(flatbuffers::FlatBufferBuilder& builder, const NodeBaseType& node)
            @endcode

            @date Tue May 01 2018
            @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
        */
        /* ---------------------------------------------------------------------------------------*/
        template<typename TConfig,
                 typename NodeSerializerList>
        class LogicNodeSerializer final
        {
        public:
            EXECGRAPH_TYPEDEF_CONFIG(TConfig);

        public:
            LogicNodeSerializer()  = default;
            ~LogicNodeSerializer() = default;

        public:
            //! Main load function for a logic node.
            //! It first tries to construct it by the factory
            //! and uses RTTR construction as a fallback.
            static std::unique_ptr<NodeBaseType>
            read(const std::string& type,
                 NodeId nodeId,
                 const std::string& nodeName,
                 const flatbuffers::Vector<uint8_t>* additionalData = nullptr)
            {
                // Dispatch to the correct serialization read function
                // the factory reads and returns the logic node
                auto rttrType = rttr::type::get_by_name(type);
                auto optNode  = FactoryRead::create(rttrType, nodeId, nodeName, additionalData);
                if(optNode)
                {
                    EXECGRAPH_THROW_IF(*optNode == nullptr,
                                       "FactoryRead::create provided nullptr for type '{0}'!",
                                       type)
                    return std::move(*optNode);
                }
                else
                {
                    EXECGRAPH_THROW_IF(additionalData != nullptr,
                                       "Cannot construct type: '{0}' without ReadFactory (add data!)!",
                                       type)
                    // try to construct over RTTR
                    EXECGRAPH_THROW_IF(!rttrType.is_derived_from(rttr::type::get<NodeBaseType>()),
                                       "Type: '{0}' is not derived from NodeBaseType!"
                                       "Did you correctly init RTTR?",
                                       type);

                    rttr::variant instance;
                    if(!nodeName.empty())
                    {
                        rttr::constructor ctor = rttrType.get_constructor({rttr::type::get<NodeId>(),
                                                                           rttr::type::get<const std::string&>()});
                        EXECGRAPH_THROW_IF(!ctor.is_valid(), "Ctor is invalid for type: '{0}'", type);
                        instance = ctor.invoke(nodeId, nodeName);
                    }
                    else
                    {
                        rttr::constructor ctor = rttrType.get_constructor({rttr::type::get<NodeId>()});
                        EXECGRAPH_THROW_IF(!ctor.is_valid(), "Ctor is invalid for type: '{0}'", type);
                        instance = ctor.invoke(nodeId);
                    }
                    EXECGRAPH_THROW_IF(!instance.is_valid(), "Variant instance is not valid!");
                    EXECGRAPH_THROW_IF(!instance.get_type().is_pointer(), "Variant instance type needs to be a pointer!");

                    return std::unique_ptr<NodeBaseType>{instance.get_value<NodeBaseType*>()};  // Return the instance
                }
            }

            //! Load a logic node from a `serialization::LogicNode`.
            static std::unique_ptr<NodeBaseType>
            read(const serialization::LogicNode& logicNode)
            {
                return LogicNodeSerializer::read(logicNode.type()->str(),
                                                 logicNode.id(),
                                                 logicNode.name() ? logicNode.name()->str() : "",
                                                 logicNode.data());
            }

            //! Store a logic node by using the builder `builder`.
            static flatbuffers::Offset<serialization::LogicNode>
            write(flatbuffers::FlatBufferBuilder& builder,
                  const NodeBaseType& node,
                  bool serializeAdditionalData = true)
            {
                NodeId id       = node.getId();
                auto nameOffset = builder.CreateString(node.getName());

                std::string type = rttr::type::get(node).get_name().to_string();
                auto typeOffset  = builder.CreateString(type);

                // Dispatch to the correct serialization write function.
                // The factory writes the additional data of the flexbuffer `data` field
                flatbuffers::FlatBufferBuilder builderData;
                flatbuffers::Offset<flatbuffers::Vector<uint8_t>> dataOffset;

                // Write the data (optional because the factory might not have a writer)
                if(serializeAdditionalData)
                {
                    std::optional<std::pair<const uint8_t*, std::size_t>>
                        optData = FactoryWrite::create(rttr::type::get(node),
                                                       builderData,
                                                       node);
                    if(optData && optData->second != 0)
                    {
                        dataOffset = builder.CreateVector(optData->first, optData->second);
                    }
                }

                // Build the logic node
                LogicNodeBuilder lnBuilder(builder);
                lnBuilder.add_id(id);
                lnBuilder.add_type(typeOffset);
                lnBuilder.add_name(nameOffset);
                if(!dataOffset.IsNull())
                {
                    lnBuilder.add_data(dataOffset);
                }
                return lnBuilder.Finish();
            }

        private:
            //! Type `T::Writer` detector
            template<typename T, typename = int>
            struct hasWriter : std::false_type
            {};
            template<typename T>
            struct hasWriter<T, decltype((void)typename T::Writer{}, 0)> : std::true_type
            {};
            //! Type `T::Writer` detector
            template<typename T, typename = int>
            struct hasReader : std::false_type
            {};
            template<typename T>
            struct hasReader<T, decltype((void)typename T::Writer{}, 0)> : std::true_type
            {};

            template<typename T>
            using writeExtractor = typename T::Writer;
            template<typename T>
            using readExtractor = typename T::Reader;

            using CreatorListWrite = meta::transform<meta::filter<NodeSerializerList, meta::quote<hasWriter>>,
                                                     meta::quote<writeExtractor>>;
            using CreatorListRead  = meta::transform<meta::filter<NodeSerializerList, meta::quote<hasReader>>,
                                                    meta::quote<readExtractor>>;
            using FactoryWrite     = StaticFactory<CreatorListWrite>;
            using FactoryRead      = StaticFactory<CreatorListRead>;
        };
    }  // namespace serialization
}  // namespace executionGraph
#endif