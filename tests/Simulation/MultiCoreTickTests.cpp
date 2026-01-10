#include <catch2/catch_test_macros.hpp>

#include "Config/SimulationConfig.h"
#include "Simulation/Factory/SimulationFactory.h"

TEST_CASE("MultiCore Naive Tick correctness") {
    const int stepsNum = 50;
    for (const int sizesToTest[] = {1, 2, 3, 10, 100}; int size : sizesToTest) {
        auto singlecoreConfig = gol::config::SimulationConfig(size, gol::config::TickMode::SingleCore,
                                                              gol::config::EdgeMode::Toroidal,
                                                              gol::config::Ruleset::Conway).
                                                              UseSeededRandomInitialState(size);

        auto multicoreNaiveConfig = gol::config::SimulationConfig(size, gol::config::TickMode::MultiCoreNaive,
                                                              gol::config::EdgeMode::Toroidal,
                                                              gol::config::Ruleset::Conway).
                                                              UseSeededRandomInitialState(size);

        auto singlecoreSim = gol::SimulationFactory::Create(singlecoreConfig);
        auto multicoreNaiveSim = gol::SimulationFactory::Create(multicoreNaiveConfig);
        REQUIRE(singlecoreSim->GetState() == multicoreNaiveSim->GetState());
        for (int i = 0; i < stepsNum; i++) {
            singlecoreSim->Tick();
            multicoreNaiveSim->Tick();
            REQUIRE(singlecoreSim->GetState() == multicoreNaiveSim->GetState());
        }
    }

}
TEST_CASE("MultiCore Pool Tick correctness") {
    const int stepsNum = 50;
    for (const int sizesToTest[] = {1, 2, 3, 10, 100}; int size : sizesToTest) {
        auto singlecoreConfig = gol::config::SimulationConfig(size, gol::config::TickMode::SingleCore,
                                                              gol::config::EdgeMode::Toroidal,
                                                              gol::config::Ruleset::Conway).
                                                              UseSeededRandomInitialState(size);

        auto multicorePoolConfig = gol::config::SimulationConfig(size, gol::config::TickMode::MultiCorePool,
                                                              gol::config::EdgeMode::Toroidal,
                                                              gol::config::Ruleset::Conway).
                                                              UseSeededRandomInitialState(size);

        auto singlecoreSim = gol::SimulationFactory::Create(singlecoreConfig);
        auto multicorePoolSim = gol::SimulationFactory::Create(multicorePoolConfig);
        REQUIRE(singlecoreSim->GetState() == multicorePoolSim->GetState());
        for (int i = 0; i < stepsNum; i++) {
            singlecoreSim->Tick();
            multicorePoolSim->Tick();
            REQUIRE(singlecoreSim->GetState() == multicorePoolSim->GetState());
        }
    }

}