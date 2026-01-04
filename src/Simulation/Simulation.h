#pragma once
#include <memory>

#include "../Grid/GridState.h"

namespace gol {
template<typename Strategy>
class Simulation {
public:

    Simulation(int size, Strategy strategy = {}) : currentState_(size), nextState_(size), strategy_(strategy) { }

    void Tick() {
        strategy_.Tick(currentState_, nextState_);
        currentState_.Swap(nextState_);
    }

    const GridState& GetState() const {
        return currentState_;
    }

    void SetState(GridState newState) {
        currentState_.Swap(newState);
    }

    void RandomizeState(float aliveChance = DefaultAliveChance) {
        currentState_.RandomizeState(aliveChance);
    }

    void ResetState() {
        currentState_.ResetState();
    }
protected:
    Strategy strategy_;

    GridState currentState_;

    GridState nextState_;
};
}