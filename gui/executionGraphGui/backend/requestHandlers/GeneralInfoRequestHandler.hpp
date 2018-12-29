//! ========================================================================================
//!  ExecutionGraph
//!  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//!
//!  @date Mon Jan 15 2018
//!  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//!
//!  This Source Code Form is subject to the terms of the Mozilla Public
//!  License, v. 2.0. If a copy of the MPL was not distributed with this
//!  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//! ========================================================================================

#ifndef executionGraphGui_backend_requestHandlers_GeneralInfoRequestHandler_hpp
#define executionGraphGui_backend_requestHandlers_GeneralInfoRequestHandler_hpp

#include "executionGraphGui/backend/BackendRequestHandler.hpp"
#include "executionGraphGui/common/FunctionMap.hpp"

class ExecutionGraphBackend;

/* ---------------------------------------------------------------------------------------*/
/*!
    Request handler for information on graphs in the backend.

    Handles the request URLs: 
        - "general/getAllGraphTypeDescriptions"

    @date Sat Jul 07 2018
    @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
 */
/* ---------------------------------------------------------------------------------------*/

class GeneralInfoRequestHandler final : public BackendRequestHandler
{
    RTTR_ENABLE(BackendRequestHandler)

public:
    using IdNamed  = BackendRequestHandler::IdNamed;
    using Function = std::function<void(GeneralInfoRequestHandler&,
                                        const Request& request,
                                        ResponsePromise& response)>;

public:
    GeneralInfoRequestHandler(std::shared_ptr<ExecutionGraphBackend> backend,
                              const IdNamed& id = IdNamed("GeneralInfoRequestHandler"));

    void handleRequest(const Request& request, ResponsePromise& response) override;
    const std::unordered_set<std::string>& getRequestTypes() const override;

private:
    void handleGetAllGraphTypeDescriptions(const Request& request,
                                           ResponsePromise& response);

private:
    static FunctionMap<Function> initFunctionMap();
    static const FunctionMap<Function> m_functionMap;

    std::shared_ptr<ExecutionGraphBackend> m_backend;
};

#endif
