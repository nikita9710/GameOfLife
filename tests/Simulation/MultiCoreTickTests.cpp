#include <catch2/catch_test_macros.hpp>

#include "Config/SimulationConfig.h"
#include "Simulation/Factory/SimulationFactory.h"

TEST_CASE("MultiCore Tick correctness") {
    const int stepsNum = 50;
    for (const int sizesToTest[] = {1, 2, 3, 10, 100}; int size : sizesToTest) {
        auto singlecoreConfig = gol::config::SimulationConfig(size, gol::config::TickMode::SingleCore,
                                                              gol::config::EdgeMode::Toroidal,
                                                              gol::config::Ruleset::Conway).
                                                              UseSeededRandomInitialState(size);

        auto multicoreConfig = gol::config::SimulationConfig(size, gol::config::TickMode::MultiCoreNaive,
                                                              gol::config::EdgeMode::Toroidal,
                                                              gol::config::Ruleset::Conway).
                                                              UseSeededRandomInitialState(size);

        auto singlecoreSim = gol::SimulationFactory::Create(singlecoreConfig);
        auto multicoreSim = gol::SimulationFactory::Create(multicoreConfig);
        REQUIRE(singlecoreSim->GetState() == multicoreSim->GetState());
        for (int i = 0; i < stepsNum; i++) {
            singlecoreSim->Tick();
            multicoreSim->Tick();
            REQUIRE(singlecoreSim->GetState() == multicoreSim->GetState());
        }
    }

}