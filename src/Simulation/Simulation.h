#pragma once
#include <memory>

#include "GridState.h"

namespace gol {
template<typename EdgePolicy>
class TickStrategy;

template<typename EdgePolicy>
class Simulation {
public:
    using Strategy = TickStrategy<EdgePolicy>;

    Simulation(int size, std::unique_ptr<Strategy> strategy) : strategy_(std::move(strategy)), currentState_(size), nextState_(size) { }

    void Tick() {
        strategy_->Tick(currentState_, nextState_);
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
private:
    std::unique_ptr<Strategy> strategy_;

    GridState currentState_;

    GridState nextState_;
};
}