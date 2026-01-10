#pragma once
#include <vector>
#include <random>

#include "../Common.h"

namespace gol {
class DenseGrid {
public:
    explicit DenseGrid(const int size) : size_(size), state_(size_ * size_, Cell::Dead) { }

    static DenseGrid CreateFromState(int gridSize,const std::vector<Cell>& grid);

    static DenseGrid CreateRandom(int gridSize, std::mt19937& rng, float aliveCellChance = DefaultAliveChance);

    static DenseGrid CreateRandom(int gridSize, float aliveCellChance = DefaultAliveChance);

    static DenseGrid ConvertToTemplate(const DenseGrid &denseGrid) {
        return denseGrid;
    }

    [[nodiscard]] DenseGrid ConvertToDenseGrid() const {
        return *this;
    }

    void Swap(DenseGrid &other);

    void RandomizeState(float aliveCellChance);
    void RandomizeState(std::mt19937& rng, float aliveCellChance);

    void ResetState();

    void SetCell(const int index, const Cell cell) {
        state_[index] = cell;
    }

    [[nodiscard]] bool IsCellAlive(const int index) const {
        return state_[index] == Cell::Alive;
    }

    [[nodiscard]] bool IsCellAlive(const int x, const int y) const {
        return IsCellAlive(x*size_ + y);
    }

    [[nodiscard]] int GetSize() const {
        return size_;
    }

    [[nodiscard]] const std::vector<Cell>& GetData() const {
        return state_;
    }

    bool operator==(const DenseGrid &lhs) const;

private:
    const int size_;

    std::vector<Cell> state_;
};
}
