#pragma once
#include <memory>

#include "../ISimulation.h"
#include "Config/SimulationConfig.h"
#include "Grid/BitGrid.h"
#include "Grid/EdgePolicies.h"
#include "Rules/ConwayRules.h"
#include "Rules/ReplicatorRules.h"
#include "Rules/SeedsRules.h"
#include "Simulation/SimulationAdapter.h"
#include "TickEngines/MultiCoreNaiveTick.h"
#include "TickEngines/MultiCorePoolTick.h"
#include "TickEngines/SingleCoreTick.h"

namespace gol {
class SimulationFactory {
public:
    [[nodiscard]] static std::unique_ptr<ISimulation> Create(const config::SimulationConfig& config);

private:
    template<class Grid, class Engine>
    static void setInitialState(const std::unique_ptr<SimulationAdapter<Grid, Engine>> &sim, const config::SimulationConfig& config) {
        switch (config.initialState_) {
            case config::InitialState::EmptyGrid:
                break;
            case config::InitialState::RandomSeeded: {
                assert(config.randomSeed_.has_value());
                std::mt19937 rng(config.randomSeed_.value());
                auto grid = DenseGrid::CreateRandom(config.size_, rng, config.aliveChance_);
                sim->setState(std::move(grid));
            }
                break;
            case config::InitialState::Random: {
                std::mt19937 rng(std::random_device{}());
                auto grid = DenseGrid::CreateRandom(config.size_, rng, config.aliveChance_);
                sim->setState(std::move(grid));
            }
                break;
            case config::InitialState::Predefined: {
                assert(config.predefinedState_.has_value());
                sim->setState(config.predefinedState_.value());
            }
                break;
            default:
                assert(false && "Init State is missing");
        }
    }

    template<class Grid, class Engine>
    static std::unique_ptr<ISimulation> makeFactory(const config::SimulationConfig &config)  {
        auto res = std::make_unique<SimulationAdapter<Grid, Engine>>(config.size_, std::make_unique<Engine>());
        setInitialState<Grid, Engine>(res, config);
        return res;
    }

    static std::unique_ptr<ISimulation> chainGrid(const config::SimulationConfig& config) {
        switch (config.gridMode_) {
            case config::GridMode::Dense:
                return chainEdge<DenseGrid>(config);
            case config::GridMode::Bit:
                return chainEdge<BitGrid>(config);
        }
        assert(false && "Unknown Grid Mode");
    }

    template<class Grid>
    static std::unique_ptr<ISimulation> chainEdge(const config::SimulationConfig& config) {
        switch (config.edgeMode_) {
            case config::EdgeMode::Toroidal:
                return chainRuleset<Grid, ToroidalEdgePolicy>(config);
            case config::EdgeMode::Clamped:
                return chainRuleset<Grid, ClampedEdgePolicy>(config);
        }
        assert(false && "Unknown Grid Mode");
    }

    template<class Grid, class Edge>
    static std::unique_ptr<ISimulation> chainRuleset(const config::SimulationConfig& config) {
        switch (config.ruleset_) {
            case config::Ruleset::Conway:
                return chainTick<Grid, Edge, rules::ConwayRules>(config);
            case config::Ruleset::Replicator:
                return chainTick<Grid, Edge, rules::ReplicatorRules>(config);
            case config::Ruleset::Seeds:
                return chainTick<Grid, Edge, rules::SeedsRules>(config);
        }
        assert(false && "Unknown Ruleset");
    }

    template<class Grid, class Edge, class Ruleset>
    static std::unique_ptr<ISimulation> chainTick(const config::SimulationConfig& config) {
        switch (config.tickMode_) {
            case config::TickMode::SingleCore:
                return makeFactory<Grid, SingleCoreTick<Grid, Edge, Ruleset>>(config);
            case config::TickMode::MultiCoreNaive:
                return makeFactory<Grid, MultiCoreNaiveTick<Grid, Edge, Ruleset>>(config);
            case config::TickMode::MultiCorePool:
                return makeFactory<Grid, MultiCorePoolTick<Grid, Edge, Ruleset>>(config);
        }
        assert(false && "Unknown Tick Mode");
    }

    // static std::unique_ptr<ISimulation> createSingleCoreSimulation(const config::SimulationConfig& config);
    // static std::unique_ptr<ISimulation> createMultiCoreNaiveSimulation(const config::SimulationConfig& config);
    // static std::unique_ptr<ISimulation> createMultiCorePoolSimulation(const config::SimulationConfig& config);
};
}
