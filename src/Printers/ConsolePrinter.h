#pragma once
#include "Printer.h"

namespace gol {
class DenseGrid;

class ConsolePrinter : public Printer {
public:
    void PrintGrid(const DenseGrid &grid_state) const override;
    void PrintStats(double lastFrameTime, double avgFrameTime) const override;
};
}