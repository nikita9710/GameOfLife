#pragma once
#include <cstdint>

namespace gol {
constexpr int DefaultAliveChance = 70;

inline constexpr char AliveAscii = '#';
inline constexpr char DeadAscii = '.';

enum class Cell : uint8_t {
    Dead = 0,
    Alive = 1
};
}
