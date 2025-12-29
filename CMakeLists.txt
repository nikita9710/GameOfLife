cmake_minimum_required(VERSION 4.1)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 23)

add_executable(GameOfLife main.cpp
        Grid.cpp
        Grid.h
        TickStrategies/TickStrategy.h
        Common.h
        TickStrategies/SingleCoreTick.cpp
        TickStrategies/SingleCoreTick.h
        TickStrategies/GPUTick.cpp
        TickStrategies/GPUTick.h
        TickStrategies/MultiCoreTick.cpp
        TickStrategies/MultiCoreTick.h
        GridState.cpp
        GridState.h
        Printers/Printer.h
        Printers/ConsolePrinter.cpp
        Printers/ConsolePrinter.h)
