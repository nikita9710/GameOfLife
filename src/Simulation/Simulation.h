#pragma once
#include <memory>

#include "../Grid/DenseGrid.h"

namespace gol {
template<typename Grid, typename Engine>
class Simulation {
public:
    explicit Simulation(const int size, std::unique_ptr<Engine> engine) : engine_(std::move(engine)), currentState_(size), nextState_(size) { }

    void Tick() {
        engine_->Tick(currentState_, nextState_);
        currentState_.Swap(nextState_);
    }

    [[nodiscard]] const Grid& GetState() const {
        return currentState_;
    }

    void SetState(Grid newState) {
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

    Grid currentState_;

    Grid nextState_;
};
}