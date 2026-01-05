#include <catch2/catch_test_macros.hpp>

#include "Rules/ConwayRules.h"
#include "../../src/Grid/EdgePolicies.h"
#include "Simulation/Simulation.h"
#include "TickEngines/SingleCoreTick.h"
#include "Utils/GridStateFromASCII.h"

template<typename Engine>
class TestSimulation : public gol::Simulation<Engine> {
public:
    using gol::Simulation<Engine>::Simulation;

    TestSimulation(int size, Engine engine = {}) : gol::Simulation<Engine>(size, engine) { }

    Engine& Getengine() {
        return this->engine_;
    }
};

template<typename EdgePolicy, typename Rules>
class TestSingleCoreTick : public gol::SingleCoreTick<EdgePolicy, Rules> {
    public:
    TestSingleCoreTick() : gol::SingleCoreTick<EdgePolicy, Rules>() { }

    void Tick(const gol::GridState &current, gol::GridState &next) const {
        TickCallCounter++;
        gol::SingleCoreTick<EdgePolicy, Rules>::Tick(current, next);
    }
    mutable int TickCallCounter = 0;
};

TEST_CASE("Simulation Blinker test") {
    constexpr int size = 5;

    const auto engine = TestSingleCoreTick<gol::ToroidalEdgePolicy, gol::rules::ConwayRules>();
    auto simulation = TestSimulation(size, engine);
    simulation.SetState(gol::GridStateFromASCII(R"(.....
                                                   .....
                                                   .###.
                                                   .....
                                                   .....)", 5));

    const auto originalState = gol::GridStateFromASCII(R"(.....
                                                          .....
                                                          .###.
                                                          .....
                                                          .....)", 5);

    const auto expectedState = gol::GridStateFromASCII(R"(.....
                                                          ..#..
                                                          ..#..
                                                          ..#..
                                                          .....)", 5);

    for (int i = 0; i < 10; ++i) {
        REQUIRE(simulation.Getengine().TickCallCounter == i);
        simulation.Tick();
        REQUIRE(simulation.Getengine().TickCallCounter == i+1);
        if (i % 2 == 0) {
            REQUIRE(simulation.GetState() == expectedState);
        }
        else  {
            REQUIRE(simulation.GetState() == originalState);
        }
    }

}