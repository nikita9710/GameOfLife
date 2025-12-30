#ifndef GAMEOFLIFE_PRINTER_H
#define GAMEOFLIFE_PRINTER_H
#include "../Simulation/GridState.h"

class Printer {
public:
    virtual ~Printer() = default;

    virtual void PrintGrid(const GridState& grid_state) const = 0;

    virtual void PrintStats(double lastFrameTime) const = 0;
};
#endif //GAMEOFLIFE_PRINTER_H