#include "GridState.h"

#include <cassert>
#include <random>
#include <stdexcept>

namespace gol {
void GridState::Swap(GridState &other) {
    assert (size_ == other.size_);
    std::swap(state_, other.state_);
}

void GridState::RandomizeState(std::mt19937& rng, const float aliveCellChance) {
    std::bernoulli_distribution dist(aliveCellChance);

    for (int i = 0; i < size_*size_; i++) {
        state_[i] = dist(rng) ? Cell::Alive : Cell::Dead;
    }
}

void GridState::RandomizeState(const float aliveCellChance) {
    std::mt19937 rng(std::random_device{}());
    RandomizeState(rng, aliveCellChance);
}

void GridState::ResetState() {
    state_ = std::vector(size_ * size_, Cell::Dead);
}

bool GridState::operator==(const GridState &lhs) const {
    return GetSize() == lhs.GetSize() && GetData() == lhs.GetData();
}

GridState GridState::CreateFromState(const std::vector<Cell> &gridState, const int gridSize) {
    if (gridSize < 1 || gridState.size() != gridSize*gridSize) {
        throw std::invalid_argument("Grid or state size is incorrect");
    }

    auto newGrid = GridState(gridSize);
    newGrid.state_ = gridState;
    return newGrid;
}

GridState GridState::CreateRandom(const int gridSize, std::mt19937& rng, const float aliveCellChance) {
    if (gridSize < 1) {
        throw std::invalid_argument("Grid size is incorrect");
    }

    auto newGrid = GridState(gridSize);
    newGrid.RandomizeState(rng, aliveCellChance);
    return newGrid;
}

GridState GridState::CreateRandom(const int gridSize, const float aliveCellChance) {
    std::mt19937 rng(std::random_device{}());
    return CreateRandom(gridSize, rng, aliveCellChance);
}
}