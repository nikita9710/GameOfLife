add_executable(tests ASCIIParserTests.cpp)
target_link_libraries(tests PRIVATE gol Catch2::Catch2WithMain)