#include "GridState.h"

#include <cassert>
#include <random>
#include <stdexcept>

namespace gol {
void GridState::Swap(GridState &other) {
    assert (size_ == other.size_);
    std::swap(state_, other.state_);
}

void GridState::RandomizeState(const int aliveCellChance) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,99);

    for (int i = 0; i < size_*size_; i++) {
        state_[i] = dist(rng) < aliveCellChance ? Cell::Alive : Cell::Dead;
    }
}

void GridState::ResetState() {
    state_ = std::vector(size_ * size_, Cell::Dead);
}

GridState GridState::CreateFromState(const std::vector<Cell> &gridState, const int gridSize) {
    if (gridSize < 1 || gridState.size() != gridSize*gridSize) {
        throw std::invalid_argument("Grid or state size is incorrect");
    }

    auto newGrid = GridState(gridSize);
    newGrid.state_ = gridState;
    return newGrid;
}

GridState GridState::CreateRandom(const int gridSize, const int aliveCellChance) {
    if (gridSize < 1) {
        throw std::invalid_argument("Grid size is incorrect");
    }

    auto newGrid = GridState(gridSize);
    newGrid.RandomizeState(aliveCellChance);
    return newGrid;
}


int GridState::GetNeighboringAliveCellsCount(const int x, const int y) const {
    int res = 0;

    for (const auto&[dx, dy]: neighboursMatrix_) {
        //toroidal wrapping => bottom row considered a neighbour of top row, same for right/left
        const int nx = (x + dx + size_) % size_;
        const int ny = (y + dy + size_) % size_;
        res += IsCellAlive(nx * size_ + ny);
    }

    return res;
}
}