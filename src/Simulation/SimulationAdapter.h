#pragma once
#include "ISimulation.h"
#include "Simulation.h"

namespace gol {
template<typename Engine>
class SimulationAdapter : public ISimulation {
public:
    SimulationAdapter(int size, Engine engine = {}) : sim_(size, std::move(engine)) { }

    void Tick() override {
        sim_.Tick();
    }

    const GridState & GetState() const override {
        return sim_.GetState();
    }

private:
    Simulation<Engine> sim_;
};
}
