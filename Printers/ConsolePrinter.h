#ifndef GAMEOFLIFE_CONSOLEPRINTER_H
#define GAMEOFLIFE_CONSOLEPRINTER_H
#include "Printer.h"


class GridState;

class ConsolePrinter : public Printer {
public:
    void PrintGrid(const GridState &grid_state) const override;
    void PrintStats(double lastFrameTime) const override;
};


#endif //GAMEOFLIFE_CONSOLEPRINTER_H