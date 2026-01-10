#include <catch2/catch_test_macros.hpp>

#include "../../src/Grid/BitGrid.h"
#include "Utils/GridStateFromASCII.h"

TEST_CASE("BitGrid Constructor initializes to dead") {
    {
        auto emptyGrid = gol::BitGrid(1);
        const auto expectedGrid = gol::GridStateFromASCII<gol::BitGrid>(1, ".");

        REQUIRE(emptyGrid == expectedGrid);
    }
    {
        auto emptyGrid = gol::BitGrid(3);
        const auto expectedGrid = gol::GridStateFromASCII<gol::BitGrid>(3, ".........");

        REQUIRE(emptyGrid == expectedGrid);
    }
}

TEST_CASE("BitGrid operator== behavior") {
    {
        auto grid1 = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#..#");
        const auto expectedGrid1 = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#..#");

        REQUIRE(grid1 == expectedGrid1);

        grid1.SetCell(0, gol::Cell::Alive);
        REQUIRE_FALSE(grid1 == expectedGrid1);

        const auto grid2 = gol::BitGrid(3);
        const auto expectedGrid2 = gol::BitGrid(2);

        REQUIRE_FALSE(grid2 == expectedGrid2);
    }
}

TEST_CASE("BitGrid ResetState behavior") {
    {
        auto resetGrid = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#..#");
        resetGrid.ResetState();
        const auto expectedGrid = gol::BitGrid(3);

        REQUIRE(resetGrid == expectedGrid);
    }
}

TEST_CASE("BitGrid Swap behavior") {
    {
        auto grid1 = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#..#");
        const auto expectedGrid1 = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#..#");

        auto grid2 = gol::GridStateFromASCII<gol::BitGrid>(3, "#..#..#..");
        const auto expectedGrid2 = gol::GridStateFromASCII<gol::BitGrid>(3, "#..#..#..");

        REQUIRE(grid1 == expectedGrid1);
        REQUIRE(grid2 == expectedGrid2);

        grid1.Swap(grid2);

        REQUIRE(grid1 == expectedGrid2);
        REQUIRE(grid2 == expectedGrid1);
    }

    {
        auto grid1 = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#..#");
        const auto expectedGrid1 = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#..#");

        REQUIRE(grid1 == expectedGrid1);

        grid1.Swap(grid1);

        REQUIRE(grid1 == expectedGrid1);
    }
}

TEST_CASE("BitGrid Invalid input") {
    REQUIRE_THROWS_AS(gol::BitGrid::CreateRandom(0), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::BitGrid::CreateFromState(0, {}), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::BitGrid::CreateFromState(0, {  gol::Cell::Dead, gol::Cell::Alive,
                                                                            gol::Cell::Dead, gol::Cell::Dead}),
                                                            std::invalid_argument);
    REQUIRE_THROWS_AS(gol::BitGrid::CreateFromState(-2, {  gol::Cell::Dead, gol::Cell::Alive,
                                                                            gol::Cell::Dead, gol::Cell::Dead}),
                                                            std::invalid_argument);
    REQUIRE_THROWS_AS(gol::BitGrid::CreateFromState(3, {  gol::Cell::Dead, gol::Cell::Alive,
                                                                            gol::Cell::Dead, gol::Cell::Dead}),
                                                            std::invalid_argument);
}

TEST_CASE("BitGrid Deterministic random initialization") {
    {
        std::mt19937 rng(42);
        const auto randomGrid = gol::BitGrid::CreateRandom(3, rng, 0.3);

        const auto expectedGrid = gol::GridStateFromASCII<gol::BitGrid>(3, ".#...#..#");

        REQUIRE(randomGrid == expectedGrid);
    }
    {
        std::mt19937 rng(21);
        auto randomGrid = gol::BitGrid(3);
        randomGrid.RandomizeState(rng, 0.3);

        const auto expectedGrid = gol::GridStateFromASCII<gol::BitGrid>(3, "..#..#...");

        REQUIRE(randomGrid == expectedGrid);
    }
    {
        std::mt19937 rng1(42);
        const auto randomGrid = gol::BitGrid::CreateRandom(3, rng1, 0.3);

        std::mt19937 rng2(42);
        auto randomGridFromEmpty = gol::BitGrid(3);
        randomGridFromEmpty.RandomizeState(rng2, 0.3);

        REQUIRE(randomGrid == randomGridFromEmpty);
    }
}