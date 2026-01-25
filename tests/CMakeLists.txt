add_executable(tests Grid/ASCIIParserTests.cpp
        Grid/DenseGridTests.cpp
        Rules/RulesNextStatesTests.cpp
        Simulation/SingleCoreTickTests.cpp
        Simulation/SimulationTests.cpp
        Grid/NeighboursCounterTests.cpp
        Simulation/SimulationFactoryTests.cpp
        ../src/Utils/magic_enum.hpp
        CLI/CLIParserTests.cpp
        Simulation/MultiCoreTickTests.cpp
        Grid/BitGridTests.cpp)
target_link_libraries(tests PRIVATE gol Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)