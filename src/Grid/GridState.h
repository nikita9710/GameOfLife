#pragma once
#include <vector>
#include <array>
#include <random>

#include "../Common.h"

namespace gol {
class GridState {
public:
    GridState(int size) : size_(size), state_(size_ * size_, Cell::Dead) { }

    static GridState CreateFromState(const std::vector<Cell>& gridState, int gridSize);

    static GridState CreateRandom(int gridSize, std::mt19937& rng, float aliveCellChance = DefaultAliveChance);

    static GridState CreateRandom(int gridSize, float aliveCellChance = DefaultAliveChance);

    void Swap(GridState &other);

    void RandomizeState(float aliveCellChance);
    void RandomizeState(std::mt19937& rng, float aliveCellChance);

    void ResetState();

    Cell& operator[](const int index) { return state_[index]; }
    const Cell& operator[](const int index) const { return state_[index]; }

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

    bool operator==(const GridState &lhs) const;

private:
    const int size_;

    std::vector<Cell> state_;
};
}
