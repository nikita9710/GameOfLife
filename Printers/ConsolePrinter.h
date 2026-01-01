#pragma once
#include "Printer.h"

namespace gol {
class GridState;

class ConsolePrinter : public Printer {
public:
    void PrintGrid(const GridState &grid_state) const override;
    void PrintStats(double lastFrameTime) const override;
};
}