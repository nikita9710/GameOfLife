#include <catch2/catch_test_macros.hpp>

#include "Rules/ConwayRules.h"
#include "Simulation/EdgePolicies.h"
#include "Simulation/Simulation.h"
#include "TickStrategies/SingleCoreTick.h"
#include "Utils/GridStateFromASCII.h"

template<typename EdgePolicy>
class TestSingleCoreTick : public gol::SingleCoreTick<EdgePolicy> {
    public:
    TestSingleCoreTick(std::unique_ptr<gol::Rules> rules) : gol::SingleCoreTick<EdgePolicy>(std::move(rules)) { }

    void Tick(const gol::GridState &current, gol::GridState &next) const override {
        TickCallCounter++;
        gol::SingleCoreTick<EdgePolicy>::Tick(current, next);
    }
    mutable int TickCallCounter = 0;
};

TEST_CASE("Simulation Blinker test") {
    constexpr int size = 5;

    auto strategy = std::make_unique<TestSingleCoreTick<gol::ToroidalEdgePolicy>>(std::make_unique<gol::ConwayRules>());
    const auto strategyPtr = strategy.get();
    REQUIRE_FALSE(strategyPtr == nullptr);

    auto simulation = gol::Simulation<gol::ToroidalEdgePolicy>(size, std::move(strategy));
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
        REQUIRE(strategyPtr->TickCallCounter == i);
        simulation.Tick();
        REQUIRE(strategyPtr->TickCallCounter == i+1);
        if (i % 2 == 0) {
            REQUIRE(simulation.GetState() == expectedState);
        }
        else  {
            REQUIRE(simulation.GetState() == originalState);
        }
    }

}