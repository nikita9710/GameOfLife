#include "BitGrid.h"

#include <cassert>
#include <random>
#include <stdexcept>

namespace gol {
    void BitGrid::Swap(BitGrid &other) {
        assert (size_ == other.size_);
        std::swap(data_, other.data_);
    }

    void BitGrid::RandomizeState(std::mt19937& rng, const float aliveCellChance) {
        std::bernoulli_distribution dist(aliveCellChance);

        for (int i = 0; i < size_*size_; i++) {
            SetCell(i, dist(rng) ? Cell::Alive : Cell::Dead);
        }
    }

    void BitGrid::RandomizeState(const float aliveCellChance) {
        std::mt19937 rng(std::random_device{}());
        RandomizeState(rng, aliveCellChance);
    }

    void BitGrid::ResetState() {
        data_ = std::vector<Word>(size_ * wordsPerRow_, 0);
    }

    bool BitGrid::operator==(const BitGrid &lhs) const {
        return GetSize() == lhs.GetSize() && GetData() == lhs.GetData();
    }

    BitGrid BitGrid::CreateFromState(const int gridSize, const std::vector<Cell> &grid) {
        if (gridSize < 1 || grid.size() != gridSize*gridSize) {
            throw std::invalid_argument("Grid or state size is incorrect");
        }

        auto newGrid = BitGrid(gridSize);
        for (int i = 0; i < gridSize*gridSize; i++) {
            newGrid.SetCell(i, grid[i]);
        }
        return newGrid;
    }

    BitGrid BitGrid::CreateRandom(const int gridSize, std::mt19937& rng, const float aliveCellChance) {
        if (gridSize < 1) {
            throw std::invalid_argument("Grid size is incorrect");
        }

        auto newGrid = BitGrid(gridSize);
        newGrid.RandomizeState(rng, aliveCellChance);
        return newGrid;
    }

    BitGrid BitGrid::CreateRandom(const int gridSize, const float aliveCellChance) {
        std::mt19937 rng(std::random_device{}());
        return CreateRandom(gridSize, rng, aliveCellChance);
    }
}