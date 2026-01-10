#pragma once
#include <optional>

#include "Common.h"
#include "Config/EdgeMode.h"
#include "Config/Ruleset.h"
#include "Config/SimulationConfig.h"
#include "Config/TickMode.h"

namespace gol::config {
struct CLIOptions {
    [[nodiscard]] SimulationConfig MakeConfig() const {
        auto config = SimulationConfig(size_, tickMode_, edgeMode_, ruleset_);
        switch (initialState_) {
            case InitialState::EmptyGrid:
                return config;

            case InitialState::RandomSeeded:
                if (!seed_) {
                    throw std::invalid_argument("Missing random seed");
                }
                return config.UseSeededRandomInitialState(seed_.value(), aliveChance_);

            case InitialState::Random:
                return config.UseRandomInitialState(aliveChance_);

            case InitialState::Predefined:
                if (!predefinedState_) {
                    throw std::invalid_argument("Missing predefined state");
                }
                return config.UsePredefinedInitialState(predefinedState_.value());
        }

        throw std::invalid_argument("Unknown initial state");
    }
private:
    friend class CLIParser;

    int size_ = 50;
    TickMode tickMode_ = TickMode::SingleCore;
    EdgeMode edgeMode_ = EdgeMode::Toroidal;
    Ruleset ruleset_ = Ruleset::Conway;
    std::optional<int> seed_;
    float aliveChance_ = DefaultAliveChance;
    std::optional<DenseGrid> predefinedState_;
    InitialState initialState_ = InitialState::EmptyGrid;
};
}
