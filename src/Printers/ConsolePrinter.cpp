#include "ConsolePrinter.h"
#include <cstdlib>
#include <iostream>
namespace gol {
void ConsolePrinter::PrintGrid(const GridState &grid_state) const {
    system("clear");
    if (grid_state.GetSize() > 50) {
        std::cout << "Grid is too big for the console, max size is 50" << std::endl;
        return;
    }
    const int size = grid_state.GetSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << (grid_state.IsCellAlive(i,j) ? AliveAscii : DeadAscii);
        }
        std::cout << std::endl;
    }
}

void ConsolePrinter::PrintStats(double lastFrameTime, double avgFrameTime) const {
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "last frame time " << lastFrameTime << "ms" << ", avg frame time " << avgFrameTime << "ms"  << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}
}