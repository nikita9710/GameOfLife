add_executable(tests Grid/ASCIIParserTests.cpp
        Grid/GridStateTests.cpp
        Rules/RulesNextStatesTests.cpp
        Simulation/SingleCoreTickTests.cpp
        Simulation/SimulationTests.cpp)
target_link_libraries(tests PRIVATE gol Catch2::Catch2WithMain)