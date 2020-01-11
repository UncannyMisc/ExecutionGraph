// =========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//
//  @date Wed Jun 06 2018
//  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// =========================================================================================

//#include <executionGraph/nodes/LogicNode.hpp>
#include <executionGraph/common/EnumFlags.hpp>
#include "TestFunctions.hpp"

using namespace executionGraph;

MY_TEST(Flags, Test)
{
    enum class E : std::size_t
    {
        A = 1 << 0,
        B = 1 << 1,
        C = 1 << 2,
        D = 1 << 3,
        E = 1 << 4
    };
    using Flags = EnumFlags<E>;

    {
        constexpr Flags f = {};
        static_assert(f.isNoneSet());
    }
    {
        constexpr Flags f = {E::D,E::A};
        static_assert(f.isSet(E::A, E::D), "Wrong");
        static_assert(f.isUnset(E::B, E::C), "Wrong");
        static_assert(f.isAnySet(E::A, E::C), "Wrong");
        static_assert(!f.isNoneSet(), "Wrong");
    }
    {
        constexpr Flags f = {E::D,E::A};
        constexpr Flags g= {E::B};
        static_assert((Flags{f,g,E::C} + Flags{E::E}).isSet(E::A,E::B,E::C,E::D,E::E), "Wrong");
    }

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
