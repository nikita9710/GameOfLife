#pragma once
#include <optional>

#include "Common.h"
#include "EdgeMode.h"
#include "Ruleset.h"
#include "TickMode.h"
#include "Grid/GridState.h"

namespace gol::config {
struct SimulationConfig {
    SimulationConfig(const int size, const TickMode tickMode, const EdgeMode edge_mode, const Ruleset ruleset) :
    size_(size), tickMode_(tickMode), edgeMode_(edge_mode), ruleset_(ruleset) {
        if (size < 1) {
            throw std::invalid_argument("Invalid size");
        }
    };

    SimulationConfig& UsePredefinedInitialState(GridState state) {
        if (state.GetSize() != size_) {
            throw std::invalid_argument("State size does not match sim size");
        }
        initialState_ = InitialState::Predefined;
        predefinedState_.emplace(std::move(state));
        randomSeed_.reset();
        return *this;
    }

    SimulationConfig& UseRandomInitialState(const float chance = DefaultAliveChance) {
        if (chance > 1.0 || chance < 0.0) {
            throw std::invalid_argument("Invalid alive chance");
        }
        initialState_ = InitialState::Random;
        aliveChance_ = chance;
        randomSeed_.reset();
        predefinedState_.reset();
        return *this;
    }

    SimulationConfig& UseSeededRandomInitialState(const uint32_t seed, const float chance = DefaultAliveChance) {
        if (chance > 1.0 || chance < 0.0) {
            throw std::invalid_argument("Invalid alive chance");
        }
        initialState_ = InitialState::RandomSeeded;
        randomSeed_ = seed;
        aliveChance_ = chance;
        predefinedState_.reset();
        return *this;
    }
private:
    friend class SimulationFactory;

    int size_;

    TickMode tickMode_;
    EdgeMode edgeMode_;
    Ruleset ruleset_;

    enum class InitialState {
        Empty,
        RandomSeeded,
        Random,
        Predefined
    } initialState_ = InitialState::Empty;

    float aliveChance_ = DefaultAliveChance;

    std::optional<uint32_t> randomSeed_;

    std::optional<GridState> predefinedState_;
};
}
