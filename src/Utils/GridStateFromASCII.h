#pragma once
#include <string_view>

#include "../Grid/GridState.h"

namespace gol {
GridState GridStateFromASCII(std::string_view ascii, int size);
}
