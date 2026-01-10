#pragma once
#include "Common.h"
#include "Grid/NeighboursCounter.h"

namespace gol {
template<typename Grid, typename EdgePolicy, typename Rules>
class RowProcessor {
public:
    static void compute(const int row, const int size, const Rules &rules, const Grid &current, Grid &next) {
        const int base = row * size;
        for (int j = 0; j < size; j++) {
            const int index = base + j;
            const int aliveNeighbours = NeighboursCounter<Grid, EdgePolicy>::Count(current, row, j);
            const bool alive = current.IsCellAlive(index);
            next.SetCell(index,
                (alive && rules.IsNextStateStable(aliveNeighbours)) ||
                (!alive && rules.IsNextStateBirth(aliveNeighbours)) ? Cell::Alive : Cell::Dead);
        }
    }
};
}
