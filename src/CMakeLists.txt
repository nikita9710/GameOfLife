add_library(gol
        Simulation/Simulation.h
        Common.h
        TickEngines/SingleCoreTick.h
        TickEngines/GPUTick.h
        TickEngines/MultiCoreTick.h
        Grid/GridState.cpp
        Grid/GridState.h
        Printers/Printer.h
        Printers/ConsolePrinter.cpp
        Printers/ConsolePrinter.h
        Rules/RulesBase.h
        Rules/ConwayRules.h
        Rules/SeedsRules.h
        Rules/ReplicatorRules.h
        Utils/GridStateFromASCII.cpp
        Utils/GridStateFromASCII.h
        Grid/EdgePolicies.h
        Grid/NeighboursCounter.h
        Simulation/SimulationAdapter.h
        Simulation/ISimulation.h
        Config/SimulationConfig.h
        Config/EdgeMode.h
        Config/Ruleset.h
        Config/TickMode.h
        Simulation/SimulationFactory.cpp
        Simulation/SimulationFactory.h)

target_include_directories(gol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(GameOfLife main.cpp)
target_link_libraries(GameOfLife PRIVATE gol)