#pragma once
#include <memory>

#include "../ISimulation.h"
#include "Config/SimulationConfig.h"
#include "Simulation/SimulationAdapter.h"

namespace gol {
class SimulationFactory {
public:
    [[nodiscard]] static std::unique_ptr<ISimulation> Create(const config::SimulationConfig& config);

private:
    template<class Grid, class Engine>
    static std::unique_ptr<ISimulation> makeFactory(const config::SimulationConfig &config)  {
        return std::make_unique<SimulationAdapter<Grid, Engine>>(config.size_, std::make_unique<Engine>());
    }
    static std::unique_ptr<ISimulation> createSingleCoreSimulation(const config::SimulationConfig& config);
    static std::unique_ptr<ISimulation> createMultiCoreNaiveSimulation(const config::SimulationConfig& config);
    static std::unique_ptr<ISimulation> createMultiCorePoolSimulation(const config::SimulationConfig& config);
};
}
