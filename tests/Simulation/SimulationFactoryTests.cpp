#include <catch2/catch_test_macros.hpp>

#include "Config/SimulationConfig.h"
#include "Utils/GridStateFromASCII.h"

TEST_CASE("Simulation Config Invalid inputs") {

    CHECK_THROWS_AS(gol::config::SimulationConfig(-1, gol::config::TickMode::SingleCore,
                                                          gol::config::EdgeMode::Toroidal,
                                                          gol::config::Ruleset::Conway), std::invalid_argument);
    auto validConfig = gol::config::SimulationConfig(3, gol::config::TickMode::SingleCore,
                                                          gol::config::EdgeMode::Toroidal,
                                                          gol::config::Ruleset::Conway);

    CHECK_THROWS_AS(validConfig.UsePredefinedInitialState(gol::GridStateFromASCII("....", 2)), std::invalid_argument);
    CHECK_THROWS_AS(validConfig.UseRandomInitialState(-1.0f), std::invalid_argument);
    CHECK_THROWS_AS(validConfig.UseRandomInitialState(2.0f), std::invalid_argument);
    CHECK_THROWS_AS(validConfig.UseSeededRandomInitialState(42, -1.0f), std::invalid_argument);
    CHECK_THROWS_AS(validConfig.UseSeededRandomInitialState(42, 2.0f), std::invalid_argument);
}