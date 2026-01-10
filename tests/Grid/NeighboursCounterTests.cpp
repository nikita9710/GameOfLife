#include "catch2/catch_test_macros.hpp"
#include "../../src/Grid/EdgePolicies.h"
#include "../../src/Grid/NeighboursCounter.h"
#include "Utils/GridStateFromASCII.h"

TEST_CASE("Toroidal Count alive neighbours") {
    using Counter = gol::NeighboursCounter<gol::DenseGrid, gol::ToroidalEdgePolicy>;
    {
        auto grid1 = gol::GridStateFromASCII<gol::DenseGrid>(1, "#");
        REQUIRE(Counter::Count(grid1, 0,0) == 8);
        auto grid2 = gol::GridStateFromASCII<gol::DenseGrid>(1, ".");
        REQUIRE(Counter::Count(grid2, 0, 0) == 0);
    }
    {
        auto grid1 = gol::GridStateFromASCII<gol::DenseGrid>(2, "....");
        REQUIRE(Counter::Count(grid1, 0,0) == 0);
        REQUIRE(Counter::Count(grid1, 0,1) == 0);
        REQUIRE(Counter::Count(grid1, 1,0) == 0);
        REQUIRE(Counter::Count(grid1, 1,1) == 0);

        auto grid2 = gol::GridStateFromASCII<gol::DenseGrid>(2, "####");
        REQUIRE(Counter::Count(grid2, 0,0) == 8);
        REQUIRE(Counter::Count(grid2, 0,1) == 8);
        REQUIRE(Counter::Count(grid2, 1,0) == 8);
        REQUIRE(Counter::Count(grid2, 1,1) == 8);

        auto grid3 = gol::GridStateFromASCII<gol::DenseGrid>(2, "#...");
        REQUIRE(Counter::Count(grid3, 0,0) == 0);
        REQUIRE(Counter::Count(grid3, 0,1) == 2);
        REQUIRE(Counter::Count(grid3, 1,0) == 2);
        REQUIRE(Counter::Count(grid3, 1,1) == 4);
    }
    {
        auto grid = gol::GridStateFromASCII<gol::DenseGrid>(3, R"(#..
                                                           .#.
                                                           ..#)");
        REQUIRE(Counter::Count(grid, 0,0) == 2);
        REQUIRE(Counter::Count(grid, 0,1) == 3);
        REQUIRE(Counter::Count(grid, 0,2) == 3);
        REQUIRE(Counter::Count(grid, 1,0) == 3);
        REQUIRE(Counter::Count(grid, 1,1) == 2);
        REQUIRE(Counter::Count(grid, 1,2) == 3);
        REQUIRE(Counter::Count(grid, 2,0) == 3);
        REQUIRE(Counter::Count(grid, 2,1) == 3);
        REQUIRE(Counter::Count(grid, 2,2) == 2);
    }
    {
        auto grid = gol::GridStateFromASCII<gol::DenseGrid>(3, R"(#..
                                                           #..
                                                           #..)");
        REQUIRE(Counter::Count(grid, 0,0) == 2);
        REQUIRE(Counter::Count(grid, 0,1) == 3);
        REQUIRE(Counter::Count(grid, 0,2) == 3);
        REQUIRE(Counter::Count(grid, 1,0) == 2);
        REQUIRE(Counter::Count(grid, 1,1) == 3);
        REQUIRE(Counter::Count(grid, 1,2) == 3);
        REQUIRE(Counter::Count(grid, 2,0) == 2);
        REQUIRE(Counter::Count(grid, 2,1) == 3);
        REQUIRE(Counter::Count(grid, 2,2) == 3);
    }
}

TEST_CASE("Clamped Count alive neighbours") {
    using Counter = gol::NeighboursCounter<gol::DenseGrid, gol::ClampedEdgePolicy>;
    {
        auto grid1 = gol::GridStateFromASCII<gol::DenseGrid>(1, "#");
        REQUIRE(Counter::Count(grid1, 0,0) == 0);
        auto grid2 = gol::GridStateFromASCII<gol::DenseGrid>(1, ".");
        REQUIRE(Counter::Count(grid2, 0, 0) == 0);
    }
    {
        auto grid1 = gol::GridStateFromASCII<gol::DenseGrid>(2, "....");
        REQUIRE(Counter::Count(grid1, 0,0) == 0);
        REQUIRE(Counter::Count(grid1, 0,1) == 0);
        REQUIRE(Counter::Count(grid1, 1,0) == 0);
        REQUIRE(Counter::Count(grid1, 1,1) == 0);

        auto grid2 = gol::GridStateFromASCII<gol::DenseGrid>(2, "####");
        REQUIRE(Counter::Count(grid2, 0,0) == 3);
        REQUIRE(Counter::Count(grid2, 0,1) == 3);
        REQUIRE(Counter::Count(grid2, 1,0) == 3);
        REQUIRE(Counter::Count(grid2, 1,1) == 3);

        auto grid3 = gol::GridStateFromASCII<gol::DenseGrid>(2, "#...");
        REQUIRE(Counter::Count(grid3, 0,0) == 0);
        REQUIRE(Counter::Count(grid3, 0,1) == 1);
        REQUIRE(Counter::Count(grid3, 1,0) == 1);
        REQUIRE(Counter::Count(grid3, 1,1) == 1);
    }
    {
        auto grid = gol::GridStateFromASCII<gol::DenseGrid>(3, R"(#..
                                                           .#.
                                                           ..#)");
        REQUIRE(Counter::Count(grid, 0,0) == 1);
        REQUIRE(Counter::Count(grid, 0,1) == 2);
        REQUIRE(Counter::Count(grid, 0,2) == 1);
        REQUIRE(Counter::Count(grid, 1,0) == 2);
        REQUIRE(Counter::Count(grid, 1,1) == 2);
        REQUIRE(Counter::Count(grid, 1,2) == 2);
        REQUIRE(Counter::Count(grid, 2,0) == 1);
        REQUIRE(Counter::Count(grid, 2,1) == 2);
        REQUIRE(Counter::Count(grid, 2,2) == 1);
    }
    {
        auto grid = gol::GridStateFromASCII<gol::DenseGrid>(3, R"(#..
                                                           #..
                                                           #..)");
        REQUIRE(Counter::Count(grid, 0,0) == 1);
        REQUIRE(Counter::Count(grid, 0,1) == 2);
        REQUIRE(Counter::Count(grid, 0,2) == 0);
        REQUIRE(Counter::Count(grid, 1,0) == 2);
        REQUIRE(Counter::Count(grid, 1,1) == 3);
        REQUIRE(Counter::Count(grid, 1,2) == 0);
        REQUIRE(Counter::Count(grid, 2,0) == 1);
        REQUIRE(Counter::Count(grid, 2,1) == 2);
        REQUIRE(Counter::Count(grid, 2,2) == 0);
    }
}