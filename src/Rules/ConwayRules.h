#pragma once
#include "RulesBase.h"

namespace gol {
struct ConwayRules : RulesBase<ConwayRules> {
    static bool isNextStateStableImpl(int aliveNeighbours) {
        return aliveNeighbours == 2 || aliveNeighbours == 3;
    }

    static bool isNextStateBirthImpl(int aliveNeighbours) {
        return aliveNeighbours == 3;
    }
};
}