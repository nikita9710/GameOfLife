#include <iostream>
#include <thread>
#include <chrono>

#include "Simulation/Simulation.h"
#include "Printers/ConsolePrinter.h"
#include "Rules/ConwayRules.h"
#include "Rules/SeedsRules.h"
#include "Rules/ReplicatorRules.h"
#include "Grid/EdgePolicies.h"
#include "TickStrategies/SingleCoreTick.h"

int main() {
    using namespace gol;
    constexpr int size = 30;
    auto simulation = Simulation<SingleCoreTick<ToroidalEdgePolicy, ConwayRules>>(size);
    simulation.RandomizeState();
    const std::unique_ptr<Printer> printer = std::make_unique<ConsolePrinter>();
    while (true) {
        auto timeBeforeTick = std::chrono::system_clock::now();
        simulation.Tick();
        const auto timeAfterTick = std::chrono::system_clock::now();
        printer->PrintGrid(simulation.GetState());
        printer->PrintStats(std::chrono::duration_cast<std::chrono::microseconds>(timeAfterTick - timeBeforeTick).count()/1000.0);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
