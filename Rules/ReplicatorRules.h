#ifndef GAMEOFLIFE_REPLICATORSRULES_H
#define GAMEOFLIFE_REPLICATORSRULES_H
#include "Rules.h"

class ReplicatorRules : public Rules {
public:
    bool IsNextStateStable(int aliveNeighbours) override {
        return aliveNeighbours == 1 || aliveNeighbours == 3 || aliveNeighbours == 5 || aliveNeighbours == 7;
    }

    bool IsNextStateBirth(int aliveNeighbours) override {
        return aliveNeighbours == 1 || aliveNeighbours == 3 || aliveNeighbours == 5 || aliveNeighbours == 7;
    }
};
#endif //GAMEOFLIFE_REPLICATORSRULES_H