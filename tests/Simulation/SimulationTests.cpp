#include <catch2/catch_test_macros.hpp>

#include "Rules/ConwayRules.h"
#include "../../src/Grid/EdgePolicies.h"
#include "Simulation/Simulation.h"
#include "TickEngines/SingleCoreTick.h"
#include "Utils/GridStateFromASCII.h"

template<typename Grid, typename Engine>
class TestSimulation : public gol::Simulation<Grid, Engine> {
public:
    using gol::Simulation<Grid, Engine>::Simulation;

    TestSimulation(int size, std::unique_ptr<Engine> engine) : gol::Simulation<Grid, Engine>(size, std::move(engine)) { }

    Engine* GetEngine() {
        return this->engine_.get();
    }
};

template<typename Grid, typename EdgePolicy, typename Rules>
class TestSingleCoreTick : public gol::SingleCoreTick<Grid, EdgePolicy, Rules> {
    public:
    TestSingleCoreTick() : gol::SingleCoreTick<Grid, EdgePolicy, Rules>() { }

    void Tick(const gol::DenseGrid &current, gol::DenseGrid &next) const {
        TickCallCounter++;
        gol::SingleCoreTick<Grid, EdgePolicy, Rules>::Tick(current, next);
    }
    mutable int TickCallCounter = 0;
};

TEST_CASE("Simulation Blinker test") {
    constexpr int size = 5;

    auto simulation =
        TestSimulation<gol::DenseGrid,TestSingleCoreTick<gol::DenseGrid, gol::ToroidalEdgePolicy, gol::rules::ConwayRules>>
            (size, std::make_unique<TestSingleCoreTick<gol::DenseGrid, gol::ToroidalEdgePolicy, gol::rules::ConwayRules>>());
    simulation.SetState(gol::GridStateFromASCII<gol::DenseGrid>(5, R"(.....
                                                               .....
                                                               .###.
                                                               .....
                                                               .....)"));

    const auto originalState = gol::GridStateFromASCII<gol::DenseGrid>(5, R"(.....
                                                                      .....
                                                                      .###.
                                                                      .....
                                                                      .....)");

    const auto expectedState = gol::GridStateFromASCII<gol::DenseGrid>(5, R"(.....
                                                                      ..#..
                                                                      ..#..
                                                                      ..#..
                                                                      .....)");

    for (int i = 0; i < 10; ++i) {
        REQUIRE(simulation.GetEngine()->TickCallCounter == i);
        simulation.Tick();
        REQUIRE(simulation.GetEngine()->TickCallCounter == i+1);
        if (i % 2 == 0) {
            REQUIRE(simulation.GetState() == expectedState);
        }
        else  {
            REQUIRE(simulation.GetState() == originalState);
        }
    }

}