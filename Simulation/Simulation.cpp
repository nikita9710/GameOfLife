#include "Simulation.h"
#include "../TickStrategies/TickStrategy.h"
#include "../Rules/Rules.h"


Simulation::Simulation(const int size, std::unique_ptr<TickStrategy> strategy): strategy_(std::move(strategy)), currentState_(size), nextState_(size) {
    currentState_.RandomizeState();
}

void Simulation::Tick() {
    strategy_->Tick(currentState_, nextState_);
    currentState_.Swap(nextState_);
}
