#ifndef GAMEOFLIFE_CONWAYRULES_H
#define GAMEOFLIFE_CONWAYRULES_H
#include "Rules.h"


class ConwayRules : public Rules {
public:
    bool IsNextStateStable(int aliveNeighbours) override {
        return aliveNeighbours == 2 || aliveNeighbours == 3;
    }

    bool IsNextStateBirth(int aliveNeighbours) override {
        return aliveNeighbours == 3;
    }
};


#endif //GAMEOFLIFE_CONWAYRULES_H