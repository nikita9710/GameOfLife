#pragma once
#include <algorithm>
#include "Common.h"
#include "Grid/NeighboursCounter.h"
#include "Grid/BitGrid.h"

namespace gol {
template<typename Grid, typename EdgePolicy, typename Rules>
class RowProcessor {
public:
    static void compute(const int row, const int size, const Rules &rules, const Grid &current, Grid &next) {
        const int base = row * size;
        for (int j = 0; j < size; j++) {
            const int index = base + j;
            const int aliveNeighbours = NeighboursCounter<Grid, EdgePolicy>::Count(current, row, j);
            const bool alive = current.IsCellAlive(index);
            next.SetCell(index,
                (alive && rules.IsNextStateStable(aliveNeighbours)) ||
                (!alive && rules.IsNextStateBirth(aliveNeighbours)) ? Cell::Alive : Cell::Dead);
        }
    }
};

template< typename EdgePolicy, typename Rules>
class RowProcessor<BitGrid, EdgePolicy, Rules> {
    public:
        static void compute(const int row, const int size, const Rules &rules, const BitGrid &current, BitGrid &next) {
            const int wordsPerRow = current.GetWordsPerRow();
            const std::vector<Word> &currentData = current.GetData();
            const size_t dataSize = currentData.size();
            // above row, current row and below
            std::vector<Word> rowNeighbourhood(wordsPerRow * 3, 0);

            Word* top    = rowNeighbourhood.data() + 0 * wordsPerRow;
            Word* mid    = rowNeighbourhood.data() + 1 * wordsPerRow;
            Word* bot = rowNeighbourhood.data() + 2 * wordsPerRow;
            Word* nextBitStart = next.GetData().data() + row*wordsPerRow;

            size_t topIndex;
            if (EdgePolicy::resolveTopWordRow(row, wordsPerRow, dataSize, topIndex))
                std::copy_n(currentData.begin() + topIndex, wordsPerRow, top);

            std::copy_n(currentData.begin() + row*wordsPerRow, wordsPerRow, mid);

            size_t bottomIndex;
            if (EdgePolicy::resolveBottomWordRow(row, wordsPerRow, size, bottomIndex))
                std::copy_n(currentData.begin() + bottomIndex, wordsPerRow, bot);

            // helper to query a single Neighbour bit
            auto getNeighbourBit = [&](const Word* rowPtr, int index) -> int {
                if constexpr (EdgePolicy::wrapsHorizontally) {
                    index = (index + size) % size;  // wrap horizontally
                } else {
                    if (index < 0 || index >= size)
                        return 0;  // clamped
                }
                // same as NeighbourIndex / wordBitSize, NeighbourIndex % wordBitSize
                return (rowPtr[index >> WordLog2] >> (index & (WordBitSize-1))) & 1;
            };

            std::fill_n(nextBitStart, wordsPerRow, Word{0});
            for (int j = 0; j < size; j++) {
                int aliveNeighbours =
                      getNeighbourBit(top, j - 1) + getNeighbourBit(top, j) + getNeighbourBit(top, j + 1)
                    + getNeighbourBit(mid, j - 1)                           + getNeighbourBit(mid, j + 1)
                    + getNeighbourBit(bot, j - 1) + getNeighbourBit(bot, j) + getNeighbourBit(bot, j + 1);

                // same as j / wordBitSize
                const int word = j >> WordLog2;
                // same as  j % wordBitSize
                const int bit = j & (WordBitSize - 1);
                bool alive = (mid[word] >> bit) & 1;
                Word &nextWord = nextBitStart[word];
                if ((alive && rules.IsNextStateStable(aliveNeighbours)) ||
                    (!alive && rules.IsNextStateBirth(aliveNeighbours))) {
                    nextWord |= (Word(1) << bit);   // set bit
                }
            }
        }
    };
}
