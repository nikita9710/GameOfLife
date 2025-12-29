//
// Created by nikita on 12/29/25.
//

#include "ConsolePrinter.h"

#include <cstdlib>
#include <iostream>

void ConsolePrinter::Print(const GridState &grid_state) const {
    system("clear");
    const int size = grid_state.GetSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << (grid_state.IsCellAlive(i,j) ? "■" : "□");
        }
        std::cout << std::endl;
    }
}
