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
    std::unique_ptr<ISimulation> result = chainGrid(config);


    return result;
}

// std::unique_ptr<ISimulation> SimulationFactory::createSingleCoreSimulation(const config::SimulationConfig &config) {
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Conway)
//         return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ToroidalEdgePolicy, rules::ConwayRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Seeds)
//         return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ToroidalEdgePolicy, rules::SeedsRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Replicator)
//         return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ToroidalEdgePolicy, rules::ReplicatorRules>>(config);
//
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Conway)
//         return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ClampedEdgePolicy, rules::ConwayRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Seeds)
//         return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ClampedEdgePolicy, rules::SeedsRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Replicator)
//         return makeFactory<DenseGrid, SingleCoreTick<DenseGrid, ClampedEdgePolicy, rules::ReplicatorRules>>(config);
//
//     assert(false && "Combination of EdgeMode and Ruleset is missing");
// }
//
//     std::unique_ptr<ISimulation> SimulationFactory::createMultiCoreNaiveSimulation(const config::SimulationConfig &config) {
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Conway)
//         return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ToroidalEdgePolicy, rules::ConwayRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Seeds)
//         return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ToroidalEdgePolicy, rules::SeedsRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Replicator)
//         return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ToroidalEdgePolicy, rules::ReplicatorRules>>(config);
//
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Conway)
//         return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ClampedEdgePolicy, rules::ConwayRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Seeds)
//         return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ClampedEdgePolicy, rules::SeedsRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Replicator)
//         return makeFactory<DenseGrid, MultiCoreNaiveTick<DenseGrid, ClampedEdgePolicy, rules::ReplicatorRules>>(config);
//
//     assert(false && "Combination of EdgeMode and Ruleset is missing");
// }
//
//     std::unique_ptr<ISimulation> SimulationFactory::createMultiCorePoolSimulation(const config::SimulationConfig &config) {
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Conway)
//         return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ToroidalEdgePolicy, rules::ConwayRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Seeds)
//         return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ToroidalEdgePolicy, rules::SeedsRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Toroidal && config.ruleset_ == config::Ruleset::Replicator)
//         return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ToroidalEdgePolicy, rules::ReplicatorRules>>(config);
//
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Conway)
//         return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ClampedEdgePolicy, rules::ConwayRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Seeds)
//         return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ClampedEdgePolicy, rules::SeedsRules>>(config);
//     if (config.edgeMode_ == config::EdgeMode::Clamped && config.ruleset_ == config::Ruleset::Replicator)
//         return makeFactory<DenseGrid, MultiCorePoolTick<DenseGrid, ClampedEdgePolicy, rules::ReplicatorRules>>(config);
//
//     assert(false && "Combination of EdgeMode and Ruleset is missing");
// }
}
