#include <catch2/catch_test_macros.hpp>

#include "Rules/ConwayRules.h"
#include "Simulation/EdgePolicies.h"
#include "Simulation/Simulation.h"
#include "TickStrategies/SingleCoreTick.h"
#include "Utils/GridStateFromASCII.h"

template<typename Strategy>
class TestSimulation : public gol::Simulation<Strategy> {
public:
    using gol::Simulation<Strategy>::Simulation;

    TestSimulation(int size, Strategy strategy = {}) : gol::Simulation<Strategy>(size, strategy) { }

    Strategy& GetStrategy() {
        return this->strategy_;
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

    const auto strategy = TestSingleCoreTick<gol::ToroidalEdgePolicy, gol::ConwayRules>();
    auto simulation = TestSimulation(size, strategy);
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
        REQUIRE(simulation.GetStrategy().TickCallCounter == i);
        simulation.Tick();
        REQUIRE(simulation.GetStrategy().TickCallCounter == i+1);
        if (i % 2 == 0) {
            REQUIRE(simulation.GetState() == expectedState);
        }
        else  {
            REQUIRE(simulation.GetState() == originalState);
        }
    }

}