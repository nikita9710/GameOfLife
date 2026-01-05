#pragma once

namespace gol {
class GridState;

class ISimulation {
public:
    virtual ~ISimulation() {};
    virtual void Tick() = 0;
    virtual const GridState& GetState() const = 0;
};
}