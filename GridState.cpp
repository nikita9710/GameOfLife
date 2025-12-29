#include "GridState.h"
#include <random>

void GridState::Swap(GridState &other) {
    using std::swap; // idiom to find the best swap (e.g., for the vector)
    swap(state_, other.state_);
}

void GridState::RandomizeState() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,9);

    for (int i = 0; i < size_*size_; i++) {
        state_[i] = dist(rng) < 7 ? DEAD : ALIVE;
    }
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
