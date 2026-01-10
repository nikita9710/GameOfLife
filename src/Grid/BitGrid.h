#pragma once
#include <cassert>
#include <vector>
#include <random>

#include "DenseGrid.h"
#include "../Common.h"

namespace gol {
class BitGrid {
public:
    using Word = uint64_t;
    explicit BitGrid(const int size) : size_(size), wordsPerRow_((size + 63)/64), data_(size_ * wordsPerRow_, 0) { }

    static BitGrid CreateFromState(int gridSize,const std::vector<Cell>& grid);

    static BitGrid CreateRandom(int gridSize, std::mt19937& rng, float aliveCellChance = DefaultAliveChance);

    static BitGrid CreateRandom(int gridSize, float aliveCellChance = DefaultAliveChance);

    static BitGrid ConvertToTemplate(const DenseGrid &denseGrid) {
        const auto size = denseGrid.GetSize();
        const auto &denseData = denseGrid.GetData();
        BitGrid res(size);
        for (int i = 0; i < size*size; ++i) {
            res.SetCell(i, denseData[i]);
        }
        return res;
    }

    [[nodiscard]] DenseGrid ConvertToDenseGrid() const {
        DenseGrid res(size_);
        for (int i = 0; i < size_*size_; ++i) {
            res.SetCell(i, IsCellAlive(i) ? Cell::Alive : Cell::Dead);
        }
        return res;
    }

    void Swap(BitGrid &other);

    void RandomizeState(float aliveCellChance);
    void RandomizeState(std::mt19937& rng, float aliveCellChance);

    void ResetState();

    void SetCell(const int index, const Cell cell) {
        const int row = index / size_;
        const int col = index % size_;
        const int word = col >> 6;
        const int bit  = col & 63;
        Word& w = data_[row * wordsPerRow_ + word];
        if (cell == Cell::Alive) {
            w |= (Word(1) << bit);
        } else {
            w &= ~(Word(1) << bit);
        }
    }

    [[nodiscard]] bool IsCellAlive(const int index) const {
        const int row = index / size_;
        const int col = index % size_;
        const int word = col >> 6;
        const int bit  = col & 63;
        return (data_[row * wordsPerRow_ + word] >> bit) & 1;
    }

    [[nodiscard]] bool IsCellAlive(const int x, const int y) const {
        return IsCellAlive(x*size_ + y);
    }

    [[nodiscard]] int GetSize() const {
        return size_;
    }

    [[nodiscard]] const std::vector<Word>& GetData() const {
        return data_;
    }

    bool operator==(const BitGrid &lhs) const;

private:
    const int size_;

    const int wordsPerRow_;

    std::vector<Word> data_;
};
}
