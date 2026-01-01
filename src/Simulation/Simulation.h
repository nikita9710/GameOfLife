#pragma once
#include <memory>

#include "GridState.h"

namespace gol {
class TickStrategy;

class Simulation {
public:
    Simulation(int size, std::unique_ptr<TickStrategy> strategy);

    void Tick();

    const GridState& GetState() const {
        return currentState_;
    }

    void SetState(GridState newState);

    void RandomizeState(int aliveChance = DefaultAliveChance);

    void ResetState();
private:
    std::unique_ptr<TickStrategy> strategy_;

    GridState currentState_;

    GridState nextState_;
};
}