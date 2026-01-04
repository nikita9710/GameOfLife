add_library(gol
        Simulation/Simulation.h
        Common.h
        TickStrategies/SingleCoreTick.h
        TickStrategies/GPUTick.h
        TickStrategies/MultiCoreTick.h
        Simulation/GridState.cpp
        Simulation/GridState.h
        Printers/Printer.h
        Printers/ConsolePrinter.cpp
        Printers/ConsolePrinter.h
        Rules/RulesBase.h
        Rules/ConwayRules.h
        Rules/SeedsRules.h
        Rules/ReplicatorRules.h
        Utils/GridStateFromASCII.cpp
        Utils/GridStateFromASCII.h
        Simulation/EdgePolicies.h
        Simulation/NeighboursCounter.h)

target_include_directories(gol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(GameOfLife main.cpp)
target_link_libraries(GameOfLife PRIVATE gol)