#include <catch2/catch_test_macros.hpp>
#include <../tests/Utils/magic_enum.hpp>

#include "Config/SimulationConfig.h"
#include "Grid/EdgePolicies.h"
#include "Rules/ConwayRules.h"
#include "Simulation/SimulationAdapter.h"
#include "../../src/Simulation/Factory/SimulationFactory.h"
#include "TickEngines/SingleCoreTick.h"
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

TEST_CASE("Simulation Factory Enums coverage") {
    for (const auto tick : magic_enum::enum_values<gol::config::TickMode>()) {
        for (const auto edge : magic_enum::enum_values<gol::config::EdgeMode>()) {
            for (const auto rules : magic_enum::enum_values<gol::config::Ruleset>()) {
                gol::config::SimulationConfig config(3, tick, edge, rules);
                auto sim = gol::SimulationFactory::Create(config);
                REQUIRE(sim != nullptr);
            }
        }
    }
}

TEST_CASE("Simulation Factory Initial states correctness") {
    {
        auto validConfig = gol::config::SimulationConfig(3, gol::config::TickMode::SingleCore,
                                                          gol::config::EdgeMode::Toroidal,
                                                          gol::config::Ruleset::Conway);
        const auto expectedInitialState = gol::GridStateFromASCII(".........", 3);
        const auto sim = gol::SimulationFactory::Create(validConfig);

        REQUIRE(sim->GetState() == expectedInitialState);
    }
    {
        std::string initStateASCII = ".#..#..#.";
        auto validConfig = gol::config::SimulationConfig(3, gol::config::TickMode::SingleCore,
                                                          gol::config::EdgeMode::Toroidal,
                                                          gol::config::Ruleset::Conway).
                                                          UsePredefinedInitialState(gol::GridStateFromASCII(initStateASCII, 3));
        const auto expectedInitialState = gol::GridStateFromASCII(initStateASCII, 3);
        const auto sim = gol::SimulationFactory::Create(validConfig);

        REQUIRE(sim->GetState() == expectedInitialState);
    }
    {
        constexpr int seed = 42;
        constexpr float aliveChance = 0.5f;
        auto validConfig = gol::config::SimulationConfig(3, gol::config::TickMode::SingleCore,
                                                          gol::config::EdgeMode::Toroidal,
                                                          gol::config::Ruleset::Conway).
                                                          UseSeededRandomInitialState(seed, aliveChance);
        auto rng = std::mt19937(seed);
        const auto expectedInitialState = gol::GridState::CreateRandom(3, rng, aliveChance);
        const auto sim = gol::SimulationFactory::Create(validConfig);

        REQUIRE(sim->GetState() == expectedInitialState);
    }
    {
        constexpr float aliveChance = 1.0f;
        auto validConfig = gol::config::SimulationConfig(3, gol::config::TickMode::SingleCore,
                                                          gol::config::EdgeMode::Toroidal,
                                                          gol::config::Ruleset::Conway).
                                                          UseRandomInitialState(aliveChance);
        const auto expectedInitialState = gol::GridStateFromASCII("#########", 3);
        const auto sim = gol::SimulationFactory::Create(validConfig);

        REQUIRE(sim->GetState() == expectedInitialState);
    }
    {
        constexpr float aliveChance = 0.0f;
        auto validConfig = gol::config::SimulationConfig(3, gol::config::TickMode::SingleCore,
                                                          gol::config::EdgeMode::Toroidal,
                                                          gol::config::Ruleset::Conway).
                                                          UseRandomInitialState(aliveChance);
        const auto expectedInitialState = gol::GridStateFromASCII(".........", 3);
        const auto sim = gol::SimulationFactory::Create(validConfig);

        REQUIRE(sim->GetState() == expectedInitialState);
    }
}