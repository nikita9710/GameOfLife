#include <catch2/catch_test_macros.hpp>

#include "Utils/GridStateFromASCII.h"

TEST_CASE("ASCII to GridState Valid input") {
    {
        const auto testGrid = gol::GridStateFromASCII(1, ".");
        const auto expectedGrid = gol::GridState::CreateFromState(1, { gol::Cell::Dead });
        REQUIRE(testGrid == expectedGrid);
    }
    {
        const auto testGrid = gol::GridStateFromASCII(2, "....");
        const auto expectedGrid = gol::GridState::CreateFromState(2, { gol::Cell::Dead, gol::Cell::Dead,
                                                                                        gol::Cell::Dead, gol::Cell::Dead});
        REQUIRE(testGrid == expectedGrid);

    }
    {
        const auto testGrid = gol::GridStateFromASCII(2, "####");
        const auto expectedGrid = gol::GridState::CreateFromState(2, { gol::Cell::Alive, gol::Cell::Alive,
                                                                                        gol::Cell::Alive, gol::Cell::Alive});
        REQUIRE(testGrid == expectedGrid);
    }
    {
        const auto testGrid = gol::GridStateFromASCII(3, ".#..#..#.");
        const auto expectedGrid = gol::GridState::CreateFromState(3, { gol::Cell::Dead, gol::Cell::Alive, gol::Cell::Dead,
                                                                                        gol::Cell::Dead, gol::Cell::Alive, gol::Cell::Dead,
                                                                                        gol::Cell::Dead, gol::Cell::Alive, gol::Cell::Dead});
        REQUIRE(testGrid == expectedGrid);
    }
    {
        const auto testGrid = gol::GridStateFromASCII(2, ".#.#");
        const auto expectedGrid = gol::GridState::CreateFromState(2, { gol::Cell::Dead, gol::Cell::Alive,
                                                                                        gol::Cell::Dead, gol::Cell::Alive});
        REQUIRE(testGrid == expectedGrid);
    }
}

TEST_CASE("ASCII to GridState Invalid input") {
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(0, ".#.#.#"), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(-2, ".#.#"), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(INT32_MAX, ".#.#.#.#."), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(3, ".#.#.#"), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(3, ".#.#.#.#.#.#.#"), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(3, ".#.#.#789"), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(3, ".#34"), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(3, "🥹🥹🥹"), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(3, ".#.#.\0#.#."), std::invalid_argument);
}

TEST_CASE("ASCII to GridState Input filtering") {
    const auto whitespaceGrid = gol::GridStateFromASCII(2, " .#     .# ");
    const auto randomCharsGrid = gol::GridStateFromASCII(2, " .# fd😝 % 7 🥹))86😅 ^%$ !@ .# ");
    const auto multilineCharsGrid = gol::GridStateFromASCII(2, R"(\n\r.#
                                                                            .#)");
    const auto expectedGrid = gol::GridState::CreateFromState(2, { gol::Cell::Dead, gol::Cell::Alive,
                                                                                    gol::Cell::Dead, gol::Cell::Alive});
    REQUIRE(whitespaceGrid == expectedGrid);
    REQUIRE(randomCharsGrid == expectedGrid);
    REQUIRE(multilineCharsGrid == expectedGrid);
}