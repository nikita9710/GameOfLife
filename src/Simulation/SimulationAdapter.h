#pragma once
#include "ISimulation.h"
#include "Simulation.h"

namespace gol {
template<typename Grid, typename Engine>
class SimulationAdapter : public ISimulation {
public:
    explicit SimulationAdapter(int size, std::unique_ptr<Engine> engine) : sim_(size, std::move(engine)) { }

    void Tick() override {
        sim_.Tick();
    }

    [[nodiscard]] const Grid & GetState() const override {
        return sim_.GetState();
    }

private:
    void setState(Grid state) override {
        sim_.SetState(state);
    }
    Simulation<Grid, Engine> sim_;
};
}
