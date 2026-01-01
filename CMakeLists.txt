cmake_minimum_required(VERSION 4.1)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameOfLife main.cpp
        src/Simulation/Simulation.cpp
        src/Simulation/Simulation.h
        src/TickStrategies/TickStrategy.cpp
        src/TickStrategies/TickStrategy.h
        src/Common.h
        src/TickStrategies/SingleCoreTick.cpp
        src/TickStrategies/SingleCoreTick.h
        src/TickStrategies/GPUTick.cpp
        src/TickStrategies/GPUTick.h
        src/TickStrategies/MultiCoreTick.cpp
        src/TickStrategies/MultiCoreTick.h
        src/Simulation/GridState.cpp
        src/Simulation/GridState.h
        src/Printers/Printer.h
        src/Printers/ConsolePrinter.cpp
        src/Printers/ConsolePrinter.h
        src/Rules/Rules.h
        src/Rules/ConwayRules.h
        src/Rules/SeedsRules.h
        src/Rules/ReplicatorRules.h)
