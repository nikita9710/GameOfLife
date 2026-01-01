#pragma once
#include <cstdint>

namespace gol {
constexpr int DefaultAliveChance = 70;

enum class Cell : uint8_t {
    Dead = 0,
    Alive = 1
};
}