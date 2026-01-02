#include <catch2/catch_test_macros.hpp>

#include "Utils/GridStateFromASCII.h"

TEST_CASE("ASCII to GridState Valid input") {
    {
        const auto testGrid = gol::GridStateFromASCII(".", 1);
        const auto expectedGrid = gol::GridState::CreateFromState({ gol::Cell::Dead }, 1);
        REQUIRE(testGrid == expectedGrid);
    }
    {
        const auto testGrid = gol::GridStateFromASCII("....", 2);
        const auto expectedGrid = gol::GridState::CreateFromState({ gol::Cell::Dead, gol::Cell::Dead,
                                                                        gol::Cell::Dead, gol::Cell::Dead},
                                                                        2);
        REQUIRE(testGrid == expectedGrid);

    }
    {
        const auto testGrid = gol::GridStateFromASCII("####", 2);
        const auto expectedGrid = gol::GridState::CreateFromState({ gol::Cell::Alive, gol::Cell::Alive,
                                                                        gol::Cell::Alive, gol::Cell::Alive},
                                                                        2);
        REQUIRE(testGrid == expectedGrid);
    }
    {
        const auto testGrid = gol::GridStateFromASCII(".#..#..#.", 3);
        const auto expectedGrid = gol::GridState::CreateFromState({ gol::Cell::Dead, gol::Cell::Alive, gol::Cell::Dead,
                                                                        gol::Cell::Dead, gol::Cell::Alive, gol::Cell::Dead,
                                                                        gol::Cell::Dead, gol::Cell::Alive, gol::Cell::Dead},
                                                                        3);
        REQUIRE(testGrid == expectedGrid);
    }
    {
        const auto testGrid = gol::GridStateFromASCII(".#.#", 2);
        const auto expectedGrid = gol::GridState::CreateFromState({ gol::Cell::Dead, gol::Cell::Alive,
                                                                        gol::Cell::Dead, gol::Cell::Alive},
                                                                        2);
        REQUIRE(testGrid == expectedGrid);
    }
}

TEST_CASE("ASCII to GridState Invalid input") {
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#.#.#", 0), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#.#", -2), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#.#.#.#.", INT32_MAX), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#.#.#", 3), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#.#.#.#.#.#.#", 3), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#.#.#789", 3), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#34", 3), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII("🥹🥹🥹", 3), std::invalid_argument);
    REQUIRE_THROWS_AS(gol::GridStateFromASCII(".#.#.\0#.#.", 3), std::invalid_argument);
}

TEST_CASE("ASCII to GridState Input filtering") {
    const auto whitespaceGrid = gol::GridStateFromASCII(" .#     .# ", 2);
    const auto randomCharsGrid = gol::GridStateFromASCII(" .# fd😝 % 7 🥹))86😅 ^%$ !@ .# ", 2);
    const auto multilineCharsGrid = gol::GridStateFromASCII(R"(\n\r.#
                                                               .#)", 2);
    const auto expectedGrid = gol::GridState::CreateFromState({ gol::Cell::Dead, gol::Cell::Alive,
                                                                    gol::Cell::Dead, gol::Cell::Alive},
                                                                    2);
    REQUIRE(whitespaceGrid == expectedGrid);
    REQUIRE(randomCharsGrid == expectedGrid);
    REQUIRE(multilineCharsGrid == expectedGrid);
}