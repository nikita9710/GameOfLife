#include <catch2/catch_test_macros.hpp>

#include "Simulation/GridState.h"
#include "Utils/GridStateFromASCII.h"

TEST_CASE("GridState Constructor initializes to dead") {
    {
        auto emptyGrid = gol::GridState(1);
        const auto expectedGrid = gol::GridStateFromASCII(".", 1);

        REQUIRE(emptyGrid == expectedGrid);
    }
    {
        auto emptyGrid = gol::GridState(3);
        const auto expectedGrid = gol::GridStateFromASCII(".........", 3);

        REQUIRE(emptyGrid == expectedGrid);
    }
}

TEST_CASE("GridState operator== behavior") {
    {
        auto grid1 = gol::GridStateFromASCII("..#..#..#", 3);
        const auto expectedGrid1 = gol::GridStateFromASCII("..#..#..#", 3);

        REQUIRE(grid1 == expectedGrid1);

        grid1[0] = gol::Cell::Alive;
        REQUIRE_FALSE(grid1 == expectedGrid1);

        const auto grid2 = gol::GridState(3);
        const auto expectedGrid2 = gol::GridState(2);

        REQUIRE_FALSE(grid2 == expectedGrid2);
    }
}

TEST_CASE("GridState ResetState behavior") {
    {
        auto resetGrid = gol::GridStateFromASCII("..#..#..#", 3);
        resetGrid.ResetState();
        const auto expectedGrid = gol::GridState(3);

        REQUIRE(resetGrid == expectedGrid);
    }
}

TEST_CASE("GridState Swap behavior") {
    {
        auto grid1 = gol::GridStateFromASCII("..#..#..#", 3);
        const auto expectedGrid1 = gol::GridStateFromASCII("..#..#..#", 3);

        auto grid2 = gol::GridStateFromASCII("#..#..#..", 3);
        const auto expectedGrid2 = gol::GridStateFromASCII("#..#..#..", 3);

        REQUIRE(grid1 == expectedGrid1);
        REQUIRE(grid2 == expectedGrid2);

        grid1.Swap(grid2);

        REQUIRE(grid1 == expectedGrid2);
        REQUIRE(grid2 == expectedGrid1);
    }

    {
        auto grid1 = gol::GridStateFromASCII("..#..#..#", 3);
        const auto expectedGrid1 = gol::GridStateFromASCII("..#..#..#", 3);

        REQUIRE(grid1 == expectedGrid1);

        grid1.Swap(grid1);

        REQUIRE(grid1 == expectedGrid1);
    }
}

TEST_CASE("Toric GridState Count alive neighbours") {
    {
        auto grid1 = gol::GridStateFromASCII("#", 1);
        REQUIRE(grid1.GetNeighbouringAliveCellsCount(0,0) == 8);
        auto grid2 = gol::GridStateFromASCII(".", 1);
        REQUIRE(grid2.GetNeighbouringAliveCellsCount(0,0) == 0);
    }
    {
        auto grid1 = gol::GridStateFromASCII("....", 2);
        REQUIRE(grid1.GetNeighbouringAliveCellsCount(0,0) == 0);
        REQUIRE(grid1.GetNeighbouringAliveCellsCount(0,1) == 0);
        REQUIRE(grid1.GetNeighbouringAliveCellsCount(1,0) == 0);
        REQUIRE(grid1.GetNeighbouringAliveCellsCount(1,1) == 0);

        auto grid2 = gol::GridStateFromASCII("####", 2);
        REQUIRE(grid2.GetNeighbouringAliveCellsCount(0,0) == 8);
        REQUIRE(grid2.GetNeighbouringAliveCellsCount(0,1) == 8);
        REQUIRE(grid2.GetNeighbouringAliveCellsCount(1,0) == 8);
        REQUIRE(grid2.GetNeighbouringAliveCellsCount(1,1) == 8);

        auto grid3 = gol::GridStateFromASCII("#...", 2);
        REQUIRE(grid3.GetNeighbouringAliveCellsCount(0,0) == 0);
        REQUIRE(grid3.GetNeighbouringAliveCellsCount(0,1) == 2);
        REQUIRE(grid3.GetNeighbouringAliveCellsCount(1,0) == 2);
        REQUIRE(grid3.GetNeighbouringAliveCellsCount(1,1) == 4);
    }
    {
        auto grid = gol::GridStateFromASCII("#...#...#", 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(0,0) == 2);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(0,1) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(0,2) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(1,0) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(1,1) == 2);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(1,2) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(2,0) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(2,1) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(2,2) == 2);
    }
    {
        auto grid = gol::GridStateFromASCII("#..#..#..", 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(0,0) == 2);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(0,1) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(0,2) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(1,0) == 2);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(1,1) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(1,2) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(2,0) == 2);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(2,1) == 3);
        REQUIRE(grid.GetNeighbouringAliveCellsCount(2,2) == 3);
    }
}

TEST_CASE("GridState Invalid input") {
    REQUIRE_THROWS_AS(gol::GridState::CreateRandom(0), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridState::CreateFromState({}, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridState::CreateFromState({  gol::Cell::Dead, gol::Cell::Alive,
                                                            gol::Cell::Dead, gol::Cell::Dead},
                                                            0), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridState::CreateFromState({  gol::Cell::Dead, gol::Cell::Alive,
                                                            gol::Cell::Dead, gol::Cell::Dead},
                                                            -2), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridState::CreateFromState({  gol::Cell::Dead, gol::Cell::Alive,
                                                            gol::Cell::Dead, gol::Cell::Dead},
                                                            3), std::invalid_argument);
}

TEST_CASE("GridState Deterministic random initialization") {
    {
        std::mt19937 rng(42);
        const auto randomGrid = gol::GridState::CreateRandom(3, rng, 0.3);

        const auto expectedGrid = gol::GridStateFromASCII(".#...#..#", 3);

        REQUIRE(randomGrid == expectedGrid);
    }
    {
        std::mt19937 rng(21);
        auto randomGrid = gol::GridState(3);
        randomGrid.RandomizeState(rng, 0.3);

        const auto expectedGrid = gol::GridStateFromASCII("..#..#...", 3);

        REQUIRE(randomGrid == expectedGrid);
    }
    {
        std::mt19937 rng1(42);
        const auto randomGrid = gol::GridState::CreateRandom(3, rng1, 0.3);

        std::mt19937 rng2(42);
        auto randomGridFromEmpty = gol::GridState(3);
        randomGridFromEmpty.RandomizeState(rng2, 0.3);

        REQUIRE(randomGrid == randomGridFromEmpty);
    }
}