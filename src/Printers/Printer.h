#pragma once
#include "../Grid/DenseGrid.h"

namespace gol {
template<typename Grid>
class Printer {
public:
    virtual ~Printer() = default;

    virtual void PrintGrid(const Grid &grid_state) const = 0;

    virtual void PrintStats(double lastFrameTime, double avgFrameTime) const = 0;
};
}