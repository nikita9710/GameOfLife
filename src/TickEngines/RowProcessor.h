#pragma once
#include "Common.h"
#include "Grid/NeighboursCounter.h"

namespace gol {
template<typename EdgePolicy, typename Rules>
class RowProcessor {
public:
    static void compute(const int row, const int size, const Rules &rules, const GridState &current, GridState &next) {
        const int base = row * size;
        for (int j = 0; j < size; j++) {
            const int index = base + j;
            const int aliveNeighbours = NeighboursCounter<EdgePolicy>::Count(current, row, j);
            const bool alive = current.IsCellAlive(index);
            next[index] =
                (alive && rules.IsNextStateStable(aliveNeighbours)) ||
                (!alive && rules.IsNextStateBirth(aliveNeighbours)) ? Cell::Alive : Cell::Dead;
        }
    }
};
}
