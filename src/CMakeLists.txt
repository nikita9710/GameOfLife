add_library(gol
        Simulation/Simulation.h
        Common.h
        TickEngines/SingleCoreTick.h
        TickEngines/GPUTick.h
        TickEngines/MultiCoreNaiveTick.h
        Grid/DenseGrid.cpp
        Grid/DenseGrid.h
        Printers/Printer.h
        Printers/ConsolePrinter.h
        Rules/RulesBase.h
        Rules/ConwayRules.h
        Rules/SeedsRules.h
        Rules/ReplicatorRules.h
        Utils/GridStateFromASCII.h
        Grid/EdgePolicies.h
        Grid/NeighboursCounter.h
        Simulation/SimulationAdapter.h
        Simulation/ISimulation.h
        Config/SimulationConfig.h
        Config/EdgeMode.h
        Config/Ruleset.h
        Config/TickMode.h
        Simulation/Factory/SimulationFactory.cpp
        Simulation/Factory/SimulationFactory.h
        CLI/CLIOptions.h
        CLI/CLIParser.cpp
        CLI/CLIParser.h
        Config/InitialState.h
        TickEngines/RowProcessor.h
        Config/GridMode.h
)

target_include_directories(gol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(GameOfLife main.cpp)
target_link_libraries(GameOfLife PRIVATE gol)