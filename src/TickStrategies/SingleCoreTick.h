#pragma once
#include "Simulation/NeighboursCounter.h"

namespace gol {
template<typename EdgePolicy, typename Rules>
class SingleCoreTick {
public:
    void Tick(const GridState &current, GridState &next) const {
        const int size = current.GetSize();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                const int index = i * size + j;
                const int aliveNeighbours = NeighboursCounter<EdgePolicy>::count(current, i, j);
                const bool alive = current.IsCellAlive(index);
                next[index] =
                    (alive && rules_.IsNextStateStable(aliveNeighbours)) ||
                    (!alive && rules_.IsNextStateBirth(aliveNeighbours)) ? Cell::Alive : Cell::Dead;
            }
        }
    }
private:
    Rules rules_;
};
}
