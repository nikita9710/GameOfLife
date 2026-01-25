cmake_minimum_required(VERSION 3.25)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 23)


include(CTest)
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(src)
add_subdirectory(tests)