#pragma once
#include "Rules.h"

namespace gol {
class ReplicatorRules : public Rules {
public:
    bool isNextStateStableImpl(int aliveNeighbours) override {
        return aliveNeighbours == 1 || aliveNeighbours == 3 || aliveNeighbours == 5 || aliveNeighbours == 7;
    }

    bool isNextStateBirthImpl(int aliveNeighbours) override {
        return aliveNeighbours == 1 || aliveNeighbours == 3 || aliveNeighbours == 5 || aliveNeighbours == 7;
    }
};
}