#ifndef GAMEOFLIFE_CONSOLEPRINTER_H
#define GAMEOFLIFE_CONSOLEPRINTER_H
#include "Printer.h"


class ConsolePrinter : public Printer {
public:
    void Print(const GridState& grid_state) const override;
};


#endif //GAMEOFLIFE_CONSOLEPRINTER_H