#include "SingleCoreTick.h"
#include "../Rules/Rules.h"

namespace gol {
SingleCoreTick::SingleCoreTick(std::unique_ptr<Rules> rules): TickStrategy(std::move(rules)) { }

void SingleCoreTick::Tick(const GridState &current, GridState &next) const {
    const int size = current.GetSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            const int index = i * size + j;
            const int aliveNeighbours = current.GetNeighbouringAliveCellsCount(i, j);
            const bool alive = current.IsCellAlive(index);
            next[index] =
                (alive && rules_->IsNextStateStable(aliveNeighbours)) ||
                (!alive && rules_->IsNextStateBirth(aliveNeighbours)) ? Cell::Alive : Cell::Dead;
        }
    }
}
}