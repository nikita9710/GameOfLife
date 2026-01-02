#pragma once
#include "Rules.h"

namespace gol {
class SeedsRules : public Rules {
public:
    bool isNextStateStableImpl(int aliveNeighbours) override {
        return false;
    }

    bool isNextStateBirthImpl(int aliveNeighbours) override {
        return aliveNeighbours == 2;
    }
};
}