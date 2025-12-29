#include <iostream>
#include <thread>
#include <vector>

#include "Grid.h"
#include "Printers/ConsolePrinter.h"
#include "TickStrategies/SingleCoreTick.h"

int main() {
    const int size = 30;

    auto grid = Grid(size, std::move(std::make_unique<SingleCoreTick>()));
    const auto printer = ConsolePrinter();
    while (true) {
        printer.Print(grid.GetState());
        grid.Tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
