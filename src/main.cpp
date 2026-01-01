#include <iostream>
#include <thread>
#include <chrono>

#include "Simulation/Simulation.h"
#include "Printers/ConsolePrinter.h"
#include "Rules/ConwayRules.h"
#include "Rules/SeedsRules.h"
#include "Rules/ReplicatorRules.h"
#include "TickStrategies/SingleCoreTick.h"

int main() {
    constexpr int size = 50;
    auto grid = gol::Simulation(size, std::move(std::make_unique<gol::SingleCoreTick>(std::make_unique<gol::ConwayRules>())));
    grid.RandomizeState();
    const std::unique_ptr<gol::Printer> printer = std::make_unique<gol::ConsolePrinter>();
    while (true) {
        auto timeBeforeTick = std::chrono::system_clock::now();
        grid.Tick();
        const auto timeAfterTick = std::chrono::system_clock::now();
        printer->PrintGrid(grid.GetState());
        printer->PrintStats(std::chrono::duration_cast<std::chrono::microseconds>(timeAfterTick - timeBeforeTick).count()/1000.0);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
