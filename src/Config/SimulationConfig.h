#pragma once
#include <optional>

#include "Common.h"
#include "EdgeMode.h"
#include "Ruleset.h"
#include "TickMode.h"
#include "Grid/GridState.h"

namespace gol::config {
struct SimulationConfig {
    int size;

    TickMode tickMode;
    EdgeMode edgeMode;
    Ruleset ruleset;

    enum class InitialState {
        Empty,
        RandomSeeded,
        Random,
        Predefined
    } initialState;

    float aliveChance = DefaultAliveChance;

    int randomSeed = 0;

    std::optional<GridState> predefinedState;
};
}
