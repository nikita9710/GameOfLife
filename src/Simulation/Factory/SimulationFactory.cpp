#include "SimulationFactory.h"

#include <utility>

#include "../SimulationAdapter.h"
#include "Grid/EdgePolicies.h"
#include "Rules/ConwayRules.h"
#include "Rules/ReplicatorRules.h"
#include "Rules/SeedsRules.h"
#include "TickEngines/MultiCoreNaiveTick.h"
#include "TickEngines/MultiCorePoolTick.h"
#include "TickEngines/SingleCoreTick.h"

namespace gol {
std::unique_ptr<ISimulation> SimulationFactory::Create(const config::SimulationConfig &config) {
    std::unique_ptr<ISimulation> result;
    switch (config.tickMode_) {
        case config::TickMode::SingleCore:
            result = createSingleCoreSimulation(config);
            break;
        case config::TickMode::MultiCoreNaive:
            result = createMultiCoreNaiveSimulation(config);
            break;
        case config::TickMode::MultiCorePool:
            result = createMultiCorePoolSimulation(config);
            break;
        default:
        assert(false && "Tick is missing");
    }
    switch (config.initialState_) {
        case config::InitialState::EmptyGrid:
            break;
        case config::InitialState::RandomSeeded: {
                assert(config.randomSeed_.has_value());
                std::mt19937 rng(config.randomSeed_.value());
                auto grid = DenseGrid::CreateRandom(config.size_, rng, config.aliveChance_);
                result->setState(std::move(grid));
            }
            break;
        case config::InitialState::Random: {
                std::mt19937 rng(std::random_device{}());
                auto grid = DenseGrid::CreateRandom(config.size_, rng, config.aliveChance_);
                result->setState(std::move(grid));
            }
            break;
        case config::InitialState::Predefined: {
                assert(config.predefinedState_.has_value());
                result->setState(config.predefinedState_.value());
            }
            break;
        default:
            assert(false && "Init State is missing");
    }

    return result;
}

std::unique_ptr<ISimulation> SimulationFactory::createSingleCoreSimulation(const config::SimulationConfig &config) {
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Conway)
        return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ToroidalEdgePolicy, rules::ConwayRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Seeds)
        return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ToroidalEdgePolicy, rules::SeedsRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Replicator)
        return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ToroidalEdgePolicy, rules::ReplicatorRules>>(config);

    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Conway)
        return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ClampedEdgePolicy, rules::ConwayRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Seeds)
        return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ClampedEdgePolicy, rules::SeedsRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Replicator)
        return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ClampedEdgePolicy, rules::ReplicatorRules>>(config);

    assert(false && "Combination of EdgeMode and Ruleset is missing");
}

    std::unique_ptr<ISimulation> SimulationFactory::createMultiCoreNaiveSimulation(const config::SimulationConfig &config) {
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Conway)
        return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ToroidalEdgePolicy, rules::ConwayRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Seeds)
        return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ToroidalEdgePolicy, rules::SeedsRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Replicator)
        return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ToroidalEdgePolicy, rules::ReplicatorRules>>(config);

    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Conway)
        return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ClampedEdgePolicy, rules::ConwayRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Seeds)
        return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ClampedEdgePolicy, rules::SeedsRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Replicator)
        return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ClampedEdgePolicy, rules::ReplicatorRules>>(config);

    assert(false && "Combination of EdgeMode and Ruleset is missing");
}

    std::unique_ptr<ISimulation> SimulationFactory::createMultiCorePoolSimulation(const config::SimulationConfig &config) {
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Conway)
        return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ToroidalEdgePolicy, rules::ConwayRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Seeds)
        return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ToroidalEdgePolicy, rules::SeedsRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Replicator)
        return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ToroidalEdgePolicy, rules::ReplicatorRules>>(config);

    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Conway)
        return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ClampedEdgePolicy, rules::ConwayRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Seeds)
        return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ClampedEdgePolicy, rules::SeedsRules>>(config);
    if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Replicator)
        return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ClampedEdgePolicy, rules::ReplicatorRules>>(config);

    assert(false && "Combination of EdgeMode and Ruleset is missing");
}
}
