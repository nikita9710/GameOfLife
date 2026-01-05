#pragma once
#include "RulesBase.h"

namespace gol::rules {
struct ReplicatorRules : RulesBase<ReplicatorRules> {
    static bool isNextStateStableImpl(int aliveNeighbours) {
        return aliveNeighbours == 1 || aliveNeighbours == 3 || aliveNeighbours == 5 || aliveNeighbours == 7;
    }

    static bool isNextStateBirthImpl(int aliveNeighbours) {
        return aliveNeighbours == 1 || aliveNeighbours == 3 || aliveNeighbours == 5 || aliveNeighbours == 7;
    }
};
}