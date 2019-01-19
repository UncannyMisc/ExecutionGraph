// =========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//
//  @date Fri Jul 06 2018
//  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// =========================================================================================

#ifndef executionGraph_serialization_SocketTypeDescription_hpp
#define executionGraph_serialization_SocketTypeDescription_hpp

#include <string>
#include <meta/meta.hpp>
#include <rttr/type>

namespace executionGraph
{
    //! A simple socket descriptio, describing a LogicSocket.
    struct SocketTypeDescription
    {
        std::string m_type;           //!< The unique RTTI name of the socket
        std::string m_name = m_type;  //!< The readable name of the socket
    };

    namespace details
    {
        //! Return a set of rtti strings.
        template<typename T>
        struct MakeRTTIs;

        //! Spezialization for `meta::list<...>`.
        template<typename... NodeType>
        struct MakeRTTIs<meta::list<NodeType...>>
        {
            template<typename T>
            static std::vector<T> eval()
            {
                return {{T{rttr::type::get<NodeType>().get_name().to_string()}...}};
            }
        };
    }  // namespace details

    //! Get all socket descriptions for this config `TConfig`.
    template<typename TConfig>
    static const std::vector<SocketTypeDescription>& getSocketDescriptions()
    {
        //! The static socket description for this default configuration
        static const std::vector<SocketTypeDescription> socketTypeDescriptions =
            details::MakeRTTIs<typename TConfig::SocketTypes>::template eval<SocketTypeDescription>();

        return socketTypeDescriptions;
    }
}  // namespace executionGraph
#endif