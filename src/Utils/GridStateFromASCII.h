#pragma once
#include <string_view>

#include "../Grid/GridState.h"

namespace gol {
[[nodiscard]] GridState GridStateFromASCII(int size, std::string_view ascii);
}
