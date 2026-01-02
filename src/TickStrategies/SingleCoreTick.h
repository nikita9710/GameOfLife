#pragma once
#include "TickStrategy.h"
#include "Simulation/NeighboursCounter.h"

namespace gol {
template<typename EdgePolicy>
class SingleCoreTick : public TickStrategy<EdgePolicy> {
public:
    explicit SingleCoreTick(std::unique_ptr<Rules> rules) : TickStrategy<EdgePolicy>(std::move(rules)) { }

    void Tick(const GridState &current, GridState &next) const override {
        const int size = current.GetSize();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                const int index = i * size + j;
                const int aliveNeighbours = NeighboursCounter<EdgePolicy>::count(current, i, j);
                const bool alive = current.IsCellAlive(index);
                next[index] =
                    (alive && this->rules_->IsNextStateStable(aliveNeighbours)) ||
                    (!alive && this->rules_->IsNextStateBirth(aliveNeighbours)) ? Cell::Alive : Cell::Dead;
            }
        }
    }

};
}
