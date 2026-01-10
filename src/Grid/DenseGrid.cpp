#include "DenseGrid.h"

#include <cassert>
#include <random>
#include <stdexcept>

namespace gol {
void DenseGrid::Swap(DenseGrid &other) {
    assert (size_ == other.size_);
    std::swap(state_, other.state_);
}

void DenseGrid::RandomizeState(std::mt19937& rng, const float aliveCellChance) {
    std::bernoulli_distribution dist(aliveCellChance);

    for (int i = 0; i < size_*size_; i++) {
        state_[i] = dist(rng) ? Cell::Alive : Cell::Dead;
    }
}

void DenseGrid::RandomizeState(const float aliveCellChance) {
    std::mt19937 rng(std::random_device{}());
    RandomizeState(rng, aliveCellChance);
}

void DenseGrid::ResetState() {
    state_ = std::vector(size_ * size_, Cell::Dead);
}

bool DenseGrid::operator==(const DenseGrid &lhs) const {
    return GetSize() == lhs.GetSize() && GetData() == lhs.GetData();
}

DenseGrid DenseGrid::CreateFromState(const int gridSize, const std::vector<Cell> &grid) {
    if (gridSize < 1 || grid.size() != gridSize*gridSize) {
        throw std::invalid_argument("Grid or state size is incorrect");
    }

    auto newGrid = DenseGrid(gridSize);
    newGrid.state_ = grid;
    return newGrid;
}

DenseGrid DenseGrid::CreateRandom(const int gridSize, std::mt19937& rng, const float aliveCellChance) {
    if (gridSize < 1) {
        throw std::invalid_argument("Grid size is incorrect");
    }

    auto newGrid = DenseGrid(gridSize);
    newGrid.RandomizeState(rng, aliveCellChance);
    return newGrid;
}

DenseGrid DenseGrid::CreateRandom(const int gridSize, const float aliveCellChance) {
    std::mt19937 rng(std::random_device{}());
    return CreateRandom(gridSize, rng, aliveCellChance);
}
}