#include "GridStateFromASCII.h"

#include <stdexcept>
#include <algorithm>

namespace gol {
GridState GridStateFromASCII(const int size, const std::string_view ascii) {
    if (size < 1) {
        throw std::invalid_argument("Grid or state size is incorrect");
    }
    const auto cellCount = size * size;
    const auto correctCharsCount = std::ranges::count(ascii, AliveAscii) + std::ranges::count(ascii, DeadAscii);
    if (correctCharsCount != cellCount) {
        throw std::invalid_argument("Invalid ASCII cell count");
    }

    GridState newState(size);

    int j = 0;
    for (int i = 0; i < cellCount; ++i) {
        while (j < ascii.size() && ascii[j] != AliveAscii && ascii[j] != DeadAscii) {
            ++j;
        }

        newState[i] = ascii[j] == AliveAscii ? Cell::Alive : Cell::Dead;
        ++j;
    }

    return newState;
}
}
