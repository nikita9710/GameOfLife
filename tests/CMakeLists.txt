add_executable(tests Grid/ASCIIParserTests.cpp
        Grid/GridStateTests.cpp
        Rules/RulesNextStatesTests.cpp
        Simulation/SingleCoreTickTests.cpp
        Simulation/SimulationTests.cpp
        Grid/NeighboursCounterTests.cpp
        Simulation/SimulationFactoryTests.cpp
        ../src/Utils/magic_enum.hpp)
target_link_libraries(tests PRIVATE gol Catch2::Catch2WithMain)