#pragma once
#include <string_view>

#include "../Grid/GridState.h"

namespace gol {
[[nodiscard]] GridState GridStateFromASCII(std::string_view ascii, int size);
}
