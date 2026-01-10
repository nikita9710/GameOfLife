#pragma once
#include "ISimulation.h"
#include "Simulation.h"

namespace gol {
template<typename Engine>
class SimulationAdapter : public ISimulation {
public:
    explicit SimulationAdapter(int size, std::unique_ptr<Engine> engine) : sim_(size, std::move(engine)) { }

    void Tick() override {
        sim_.Tick();
    }

    [[nodiscard]] const GridState & GetState() const override {
        return sim_.GetState();
    }

private:
    void setState(GridState state) override {
        sim_.SetState(state);
    }
    Simulation<Engine> sim_;
};
}
