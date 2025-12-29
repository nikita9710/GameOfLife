#ifndef GAMEOFLIFE_SEEDSRULES_H
#define GAMEOFLIFE_SEEDSRULES_H
#include "Rules.h"

class SeedsRules : public Rules {
public:
    bool IsNextStateStable(int aliveNeighbours) override {
        return false;
    }

    bool IsNextStateBirth(int aliveNeighbours) override {
        return aliveNeighbours == 2;
    }
};
#endif //GAMEOFLIFE_SEEDSRULES_H