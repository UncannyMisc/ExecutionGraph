// =========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//
//  @date Sun Jul 29 2018
//  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// =========================================================================================

#ifndef executionGraphGui_common_DevFlags_hpp
#define executionGraphGui_common_DevFlags_hpp

namespace devFlags
{
    static constexpr bool showDevTools                = true;  //!< If the DeveloperTools are shown on start up of the browser.
    static constexpr bool verifyAllFlatbufferMessages = true;  //!< If all Flatbuffer messages are verified.
}  // namespace devFlags

#endif