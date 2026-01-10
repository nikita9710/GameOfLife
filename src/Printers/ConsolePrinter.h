#pragma once
#include <iostream>

#include "Printer.h"

namespace gol {
template<typename Grid>
class ConsolePrinter : public Printer<Grid> {
public:
    void PrintGrid(const Grid &grid_state) const override {
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
    void PrintStats(const double lastFrameTime, const double avgFrameTime) const override {
        std::cout << "-----------------------------------------------------" << std::endl;
        std::cout << "last frame time " << lastFrameTime << "ms" << ", avg frame time " << avgFrameTime << "ms"  << std::endl;
        std::cout << "-----------------------------------------------------" << std::endl;
    }
};
}