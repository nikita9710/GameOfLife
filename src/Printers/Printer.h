#pragma once
#include "../Grid/GridState.h"

namespace gol {
class Printer {
public:
    virtual ~Printer() = default;

    virtual void PrintGrid(const GridState& grid_state) const = 0;

    virtual void PrintStats(double lastFrameTime, double avgFrameTime) const = 0;
};
}