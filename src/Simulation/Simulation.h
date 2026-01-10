#pragma once
#include <memory>

#include "../Grid/GridState.h"

namespace gol {
template<typename Engine>
class Simulation {
public:
    explicit Simulation(const int size, std::unique_ptr<Engine> engine) : engine_(std::move(engine)), currentState_(size), nextState_(size) { }

    void Tick() {
        engine_->Tick(currentState_, nextState_);
        currentState_.Swap(nextState_);
    }

    [[nodiscard]] const GridState& GetState() const {
        return currentState_;
    }

    void SetState(GridState newState) {
        currentState_.Swap(newState);
    }

    void RandomizeState(const float aliveChance = DefaultAliveChance) {
        currentState_.RandomizeState(aliveChance);
    }

    void ResetState() {
        currentState_.ResetState();
    }
protected:
    std::unique_ptr<Engine> engine_;

    GridState currentState_;

    GridState nextState_;
};
}