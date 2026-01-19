#pragma once
#include <cstdint>
#include <cmath>

namespace gol {
constexpr float DefaultAliveChance = 0.3;

constexpr int MaxThreadsCount = 8;

inline constexpr char AliveAscii = '#';
inline constexpr char DeadAscii = '.';

enum class Cell : uint8_t {
    Dead = 0,
    Alive = 1
};

using Word = uint64_t;

static constexpr int WordBitSize = sizeof(Word)*8;

static constexpr int WordLog2 =
    (WordBitSize == 64 ? 6 :
     WordBitSize == 32 ? 5 :
     WordBitSize == 16 ? 4 :
     WordBitSize == 8  ? 3 :
     -1);
}
