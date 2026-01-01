#pragma once
#include "Rules.h"

namespace gol {
class SeedsRules : public Rules {
public:
    bool IsNextStateStable(int aliveNeighbours) override {
        return false;
    }

    bool IsNextStateBirth(int aliveNeighbours) override {
        return aliveNeighbours == 2;
    }
};
}