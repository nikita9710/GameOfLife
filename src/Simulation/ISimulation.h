#pragma once

namespace gol {
class GridState;

class ISimulation {
public:
    virtual ~ISimulation() = default;
    virtual void Tick() = 0;
    [[nodiscard]] virtual const GridState& GetState() const = 0;
private:
    virtual void setState(GridState state) = 0;
    friend class SimulationFactory;
};
}