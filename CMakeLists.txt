cmake_minimum_required(VERSION 4.1)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameOfLife main.cpp
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
        Rules/ReplicatorRules.h)
