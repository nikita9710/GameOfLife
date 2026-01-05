#pragma once
#include <memory>

#include "../ISimulation.h"
#include "Config/SimulationConfig.h"

namespace gol {
class SimulationFactory {
public:
    [[nodiscard]] static std::unique_ptr<ISimulation> Create(const config::SimulationConfig& config);
private:
    static std::unique_ptr<ISimulation> createSingleCoreSimulation(const config::SimulationConfig& config);
    static std::unique_ptr<ISimulation> createMultiCoreSimulation(const config::SimulationConfig& config);
};
}
