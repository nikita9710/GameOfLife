#pragma once
#include <vector>
#include <array>

#include "../Common.h"

namespace gol {
class GridState {
public:
    GridState(int size) : size_(size), state_(size_ * size_, Cell::Dead) { }

    static GridState CreateFromState(const std::vector<Cell>& gridState, int gridSize);

    static GridState CreateRandom(int gridSize, int aliveCellChance = DefaultAliveChance);

    int GetNeighboringAliveCellsCount(int x, int y) const;

    void Swap(GridState &other);

    // chance from 0 to 100
    void RandomizeState(int aliveCellChance);

    void ResetState();

    Cell& operator[](int index) { return state_[index]; }
    const Cell& operator[](int index) const { return state_[index]; }

    bool IsCellAlive(const int index) const {
        return state_[index] == Cell::Alive;
    }

    bool IsCellAlive(const int x, const int y) const {
        return IsCellAlive(x*size_ + y);
    }

    int GetSize() const {
        return size_;
    }

    const std::vector<Cell>& GetData() const {
        return state_;
    }
private:
    const int size_;

    std::vector<Cell> state_;

    struct offset {
        int dx;
        int dy;
    };

    static constexpr std::array<offset, 8> neighboursMatrix_ {{
        {-1, -1}, {-1,  0}, {-1,  1},
        { 0, -1},                      { 0,  1},
        { 1, -1}, { 1,  0}, { 1,  1}
    }};
};
}