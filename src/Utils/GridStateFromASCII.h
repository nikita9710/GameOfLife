#pragma once
#include <string_view>

#include "../Simulation/GridState.h"

namespace gol {
GridState GridStateFromASCII(std::string_view ascii, int size);
}
