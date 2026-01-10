#pragma once
#include "Grid/DenseGrid.h"

namespace gol {

class ISimulation {
public:
    virtual ~ISimulation() = default;
    virtual void Tick() = 0;
    [[nodiscard]] virtual DenseGrid GetState() const = 0;
private:
    virtual void setState(DenseGrid state) = 0;
};
}