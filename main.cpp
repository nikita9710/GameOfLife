#include <iostream>
#include <thread>

#include "Simulation/Simulation.h"
#include "Printers/ConsolePrinter.h"
#include "Rules/ConwayRules.h"
#include "Rules/SeedsRules.h"
#include "Rules/ReplicatorRules.h"
#include "TickStrategies/SingleCoreTick.h"

int main() {
    const int size = 100;
    auto grid = Simulation(size, std::move(std::make_unique<SingleCoreTick>(std::make_unique<ConwayRules>())));
    const std::unique_ptr<Printer> printer = std::make_unique<ConsolePrinter>();
    while (true) {
        printer->Print(grid.GetState());
        grid.Tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
