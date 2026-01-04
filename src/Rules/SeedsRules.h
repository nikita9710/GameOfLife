#pragma once
#include "RulesBase.h"

namespace gol {
struct SeedsRules : RulesBase<SeedsRules> {
    static bool isNextStateStableImpl(int _) {
        return false;
    }

    static bool isNextStateBirthImpl(int aliveNeighbours) {
        return aliveNeighbours == 2;
    }
};
}