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

    [[nodiscard]] DenseGrid GetState() const override {
        DenseGrid res = sim_.GetState().ConvertToDenseGrid();
        return res;
    }

private:
    void setState(DenseGrid state) override {
        Grid convertedState = Grid::ConvertToTemplate(state);
        sim_.SetState(convertedState);
    }

    Simulation<Grid, Engine> sim_;

    friend class SimulationFactory;
};
}
