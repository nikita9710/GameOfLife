#pragma once
#include "Rules.h"

namespace gol {
class ConwayRules : public Rules {
public:
    bool isNextStateStableImpl(int aliveNeighbours) override {
        return aliveNeighbours == 2 || aliveNeighbours == 3;
    }

    bool isNextStateBirthImpl(int aliveNeighbours) override {
        return aliveNeighbours == 3;
    }
};
}