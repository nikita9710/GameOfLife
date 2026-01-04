#include <catch2/catch_test_macros.hpp>

#include "Rules/ConwayRules.h"
#include "Simulation/EdgePolicies.h"
#include "TickStrategies/SingleCoreTick.h"
#include "Utils/GridStateFromASCII.h"

TEST_CASE("Single Core Tick Conway Toroidal Blinker pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(.....
                                                         .....
                                                         .###.
                                                         .....
                                                         .....)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(.....
                                                          .....
                                                          .###.
                                                          .....
                                                          .....)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(.....
                                                          ..#..
                                                          ..#..
                                                          ..#..
                                                          .....)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ToroidalEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Toroidal over edge Blinker pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(..#..
                                                         ..#..
                                                         .....
                                                         .....
                                                         ..#..)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(..#..
                                                          ..#..
                                                          .....
                                                          .....
                                                          ..#..)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(.###.
                                                          .....
                                                          .....
                                                          .....
                                                          .....)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ToroidalEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);

        tickStrategy.Tick(expectedState, nextState1);

        REQUIRE(nextState1 == originalState);

    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);

        tickStrategy.Tick(expectedState, nextState2);

        REQUIRE(nextState2 == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Toroidal over edge Block pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(#...#
                                                         .....
                                                         .....
                                                         .....
                                                         #...#)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(#...#
                                                          .....
                                                          .....
                                                          .....
                                                          #...#)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(#...#
                                                          .....
                                                          .....
                                                          .....
                                                          #...#)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ToroidalEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Toroidal Block pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(.....
                                                         .##..
                                                         .##..
                                                         .....
                                                         .....)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(.....
                                                          .##..
                                                          .##..
                                                          .....
                                                          .....)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(.....
                                                          .##..
                                                          .##..
                                                          .....
                                                          .....)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ToroidalEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);

    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Toroidal Overpopulation") {
    const auto currentState = gol::GridStateFromASCII("#########################", 5);
    const auto originalState = gol::GridStateFromASCII("#########################", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(".........................", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ToroidalEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Toroidal All dead") {
    const auto currentState = gol::GridStateFromASCII(".........................", 5);
    const auto originalState = gol::GridStateFromASCII(".........................", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(".........................", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ToroidalEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Clamped Blinker pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(.....
                                                         .....
                                                         .###.
                                                         .....
                                                         .....)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(.....
                                                          .....
                                                          .###.
                                                          .....
                                                          .....)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(.....
                                                          ..#..
                                                          ..#..
                                                          ..#..
                                                          .....)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ClampedEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Clamped over edge Blinker pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(..#..
                                                         ..#..
                                                         .....
                                                         .....
                                                         ..#..)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(..#..
                                                          ..#..
                                                          .....
                                                          .....
                                                          ..#..)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(.....
                                                          .....
                                                          .....
                                                          .....
                                                          .....)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ClampedEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);

        tickStrategy.Tick(expectedState, nextState1);

        REQUIRE(nextState1 == expectedState);

    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);

        tickStrategy.Tick(expectedState, nextState2);

        REQUIRE(nextState2 == expectedState);
    }
}

TEST_CASE("Single Core Tick Conway Clamped over edge Block pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(#...#
                                                         .....
                                                         .....
                                                         .....
                                                         #...#)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(#...#
                                                          .....
                                                          .....
                                                          .....
                                                          #...#)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(.....
                                                          .....
                                                          .....
                                                          .....
                                                          .....)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ClampedEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Clamped Block pattern") {
    const auto currentState = gol::GridStateFromASCII(R"(.....
                                                         .##..
                                                         .##..
                                                         .....
                                                         .....)", 5);
    const auto originalState = gol::GridStateFromASCII(R"(.....
                                                          .##..
                                                          .##..
                                                          .....
                                                          .....)", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(R"(.....
                                                          .##..
                                                          .##..
                                                          .....
                                                          .....)", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ClampedEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);

    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}

TEST_CASE("Single Core Tick Conway Clamped Overpopulation") {
    const auto currentState = gol::GridStateFromASCII("#########################", 5);
    const auto originalState = gol::GridStateFromASCII("#########################", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState1 = gol::GridStateFromASCII("#...#...............#...#", 5);
    const auto expectedState2 = gol::GridStateFromASCII(".........................", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ClampedEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState1);
        REQUIRE(currentState == originalState);

        tickStrategy.Tick(expectedState1, nextState1);

        REQUIRE(nextState1 == expectedState2);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState1);
        REQUIRE(currentState == originalState);

        tickStrategy.Tick(expectedState1, nextState2);

        REQUIRE(nextState1 == expectedState2);
    }
}

TEST_CASE("Single Core Tick Conway Clamped All dead") {
    const auto currentState = gol::GridStateFromASCII(".........................", 5);
    const auto originalState = gol::GridStateFromASCII(".........................", 5);
    auto nextState1 = gol::GridStateFromASCII(".........................", 5);
    auto nextState2 = gol::GridStateFromASCII("#########################", 5);
    const auto expectedState = gol::GridStateFromASCII(".........................", 5);

    const auto tickStrategy = gol::SingleCoreTick<gol::ClampedEdgePolicy, gol::ConwayRules>();
    {
        tickStrategy.Tick(currentState, nextState1);

        REQUIRE(nextState1 == expectedState);
        REQUIRE(currentState == originalState);
    }
    {
        tickStrategy.Tick(currentState, nextState2);

        REQUIRE(nextState2 == expectedState);
        REQUIRE(currentState == originalState);
    }
}