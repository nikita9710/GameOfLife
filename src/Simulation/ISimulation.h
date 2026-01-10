#pragma once

namespace gol {
class DenseGrid;

class ISimulation {
public:
    virtual ~ISimulation() = default;
    virtual void Tick() = 0;
    [[nodiscard]] virtual const DenseGrid& GetState() const = 0;
private:
    virtual void setState(DenseGrid state) = 0;
    friend class SimulationFactory;
};
}