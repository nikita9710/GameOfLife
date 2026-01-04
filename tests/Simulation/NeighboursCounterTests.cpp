#include "catch2/catch_test_macros.hpp"
#include "Rules/ConwayRules.h"
#include "../../src/Grid/EdgePolicies.h"
#include "../../src/Grid/NeighboursCounter.h"
#include "TickStrategies/SingleCoreTick.h"
#include "Utils/GridStateFromASCII.h"

TEST_CASE("Toroidal Count alive neighbours") {
    using Counter = gol::NeighboursCounter<gol::ToroidalEdgePolicy>;
    {
        auto grid1 = gol::GridStateFromASCII("#", 1);
        REQUIRE(Counter::count(grid1, 0,0) == 8);
        auto grid2 = gol::GridStateFromASCII(".", 1);
        REQUIRE(Counter::count(grid2, 0, 0) == 0);
    }
    {
        auto grid1 = gol::GridStateFromASCII("....", 2);
        REQUIRE(Counter::count(grid1, 0,0) == 0);
        REQUIRE(Counter::count(grid1, 0,1) == 0);
        REQUIRE(Counter::count(grid1, 1,0) == 0);
        REQUIRE(Counter::count(grid1, 1,1) == 0);

        auto grid2 = gol::GridStateFromASCII("####", 2);
        REQUIRE(Counter::count(grid2, 0,0) == 8);
        REQUIRE(Counter::count(grid2, 0,1) == 8);
        REQUIRE(Counter::count(grid2, 1,0) == 8);
        REQUIRE(Counter::count(grid2, 1,1) == 8);

        auto grid3 = gol::GridStateFromASCII("#...", 2);
        REQUIRE(Counter::count(grid3, 0,0) == 0);
        REQUIRE(Counter::count(grid3, 0,1) == 2);
        REQUIRE(Counter::count(grid3, 1,0) == 2);
        REQUIRE(Counter::count(grid3, 1,1) == 4);
    }
    {
        auto grid = gol::GridStateFromASCII(R"(#..
                                               .#.
                                               ..#)", 3);
        REQUIRE(Counter::count(grid, 0,0) == 2);
        REQUIRE(Counter::count(grid, 0,1) == 3);
        REQUIRE(Counter::count(grid, 0,2) == 3);
        REQUIRE(Counter::count(grid, 1,0) == 3);
        REQUIRE(Counter::count(grid, 1,1) == 2);
        REQUIRE(Counter::count(grid, 1,2) == 3);
        REQUIRE(Counter::count(grid, 2,0) == 3);
        REQUIRE(Counter::count(grid, 2,1) == 3);
        REQUIRE(Counter::count(grid, 2,2) == 2);
    }
    {
        auto grid = gol::GridStateFromASCII(R"(#..
                                               #..
                                               #..)", 3);
        REQUIRE(Counter::count(grid, 0,0) == 2);
        REQUIRE(Counter::count(grid, 0,1) == 3);
        REQUIRE(Counter::count(grid, 0,2) == 3);
        REQUIRE(Counter::count(grid, 1,0) == 2);
        REQUIRE(Counter::count(grid, 1,1) == 3);
        REQUIRE(Counter::count(grid, 1,2) == 3);
        REQUIRE(Counter::count(grid, 2,0) == 2);
        REQUIRE(Counter::count(grid, 2,1) == 3);
        REQUIRE(Counter::count(grid, 2,2) == 3);
    }
}

TEST_CASE("Clamped Count alive neighbours") {
    using Counter = gol::NeighboursCounter<gol::ClampedEdgePolicy>;
    {
        auto grid1 = gol::GridStateFromASCII("#", 1);
        REQUIRE(Counter::count(grid1, 0,0) == 0);
        auto grid2 = gol::GridStateFromASCII(".", 1);
        REQUIRE(Counter::count(grid2, 0, 0) == 0);
    }
    {
        auto grid1 = gol::GridStateFromASCII("....", 2);
        REQUIRE(Counter::count(grid1, 0,0) == 0);
        REQUIRE(Counter::count(grid1, 0,1) == 0);
        REQUIRE(Counter::count(grid1, 1,0) == 0);
        REQUIRE(Counter::count(grid1, 1,1) == 0);

        auto grid2 = gol::GridStateFromASCII("####", 2);
        REQUIRE(Counter::count(grid2, 0,0) == 3);
        REQUIRE(Counter::count(grid2, 0,1) == 3);
        REQUIRE(Counter::count(grid2, 1,0) == 3);
        REQUIRE(Counter::count(grid2, 1,1) == 3);

        auto grid3 = gol::GridStateFromASCII("#...", 2);
        REQUIRE(Counter::count(grid3, 0,0) == 0);
        REQUIRE(Counter::count(grid3, 0,1) == 1);
        REQUIRE(Counter::count(grid3, 1,0) == 1);
        REQUIRE(Counter::count(grid3, 1,1) == 1);
    }
    {
        auto grid = gol::GridStateFromASCII(R"(#..
                                               .#.
                                               ..#)", 3);
        REQUIRE(Counter::count(grid, 0,0) == 1);
        REQUIRE(Counter::count(grid, 0,1) == 2);
        REQUIRE(Counter::count(grid, 0,2) == 1);
        REQUIRE(Counter::count(grid, 1,0) == 2);
        REQUIRE(Counter::count(grid, 1,1) == 2);
        REQUIRE(Counter::count(grid, 1,2) == 2);
        REQUIRE(Counter::count(grid, 2,0) == 1);
        REQUIRE(Counter::count(grid, 2,1) == 2);
        REQUIRE(Counter::count(grid, 2,2) == 1);
    }
    {
        auto grid = gol::GridStateFromASCII(R"(#..
                                               #..
                                               #..)", 3);
        REQUIRE(Counter::count(grid, 0,0) == 1);
        REQUIRE(Counter::count(grid, 0,1) == 2);
        REQUIRE(Counter::count(grid, 0,2) == 0);
        REQUIRE(Counter::count(grid, 1,0) == 2);
        REQUIRE(Counter::count(grid, 1,1) == 3);
        REQUIRE(Counter::count(grid, 1,2) == 0);
        REQUIRE(Counter::count(grid, 2,0) == 1);
        REQUIRE(Counter::count(grid, 2,1) == 2);
        REQUIRE(Counter::count(grid, 2,2) == 0);
    }
}