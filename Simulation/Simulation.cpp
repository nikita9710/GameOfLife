#include "Simulation.h"
#include "../TickStrategies/TickStrategy.h"
#include "../Rules/Rules.h"

namespace gol {
Simulation::Simulation(const int size, std::unique_ptr<TickStrategy> strategy): strategy_(std::move(strategy)), currentState_(size), nextState_(size) {

}

void Simulation::Tick() {
    strategy_->Tick(currentState_, nextState_);
    currentState_.Swap(nextState_);
}

void Simulation::RandomizeState(const int aliveChance) {
    currentState_.RandomizeState(aliveChance);
}

void Simulation::ResetState() {
    currentState_.ResetState();
}

void Simulation::SetState(GridState newState) {
    currentState_.Swap(newState);
}
}