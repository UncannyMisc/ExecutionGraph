// ========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <nuetzig (at) imes (d0t) mavt (d0t) ethz
//  (døt) ch>
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================================

#ifndef ExecutionGraph_Common_StaticAssert_hpp
#define ExecutionGraph_Common_StaticAssert_hpp

#include <type_traits>

namespace ExecutionGraph
{
#define EXEC_GRAPH_STATIC_ASSERT(B) static_assert(B, "no message");
#define EXEC_GRAPH_STATIC_ASSERTM(B, COMMENT) static_assert(B, COMMENT);
}

#endif
