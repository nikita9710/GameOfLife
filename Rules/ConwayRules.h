#pragma once
#include "Rules.h"

namespace gol {
class ConwayRules : public Rules {
public:
    bool IsNextStateStable(int aliveNeighbours) override {
        return aliveNeighbours == 2 || aliveNeighbours == 3;
    }

    bool IsNextStateBirth(int aliveNeighbours) override {
        return aliveNeighbours == 3;
    }
};
}