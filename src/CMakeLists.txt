add_library(gol
        Simulation/Simulation.cpp
        Simulation/Simulation.h
        TickStrategies/TickStrategy.cpp
        TickStrategies/TickStrategy.h
        Common.h
        TickStrategies/SingleCoreTick.cpp
        TickStrategies/SingleCoreTick.h
        TickStrategies/GPUTick.cpp
        TickStrategies/GPUTick.h
        TickStrategies/MultiCoreTick.cpp
        TickStrategies/MultiCoreTick.h
        Simulation/GridState.cpp
        Simulation/GridState.h
        Printers/Printer.h
        Printers/ConsolePrinter.cpp
        Printers/ConsolePrinter.h
        Rules/Rules.h
        Rules/ConwayRules.h
        Rules/SeedsRules.h
        Rules/ReplicatorRules.h
        Utils/GridStateFromASCII.cpp
        Utils/GridStateFromASCII.h)

target_include_directories(gol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(GameOfLife main.cpp)
target_link_libraries(GameOfLife PRIVATE gol)