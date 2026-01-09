#pragma once
#include <cassert>
#include <thread>

#include "Grid/NeighboursCounter.h"

namespace gol {
template<typename EdgePolicy, typename Rules>
class MultiCoreTick {
public:
    void Tick(const GridState &current, GridState &next) const {
        const int size = current.GetSize();
        const int threadsCount = std::min(MaxThreadsCound, size);

        std::vector<std::jthread> threads;
        threads.reserve(threadsCount);

        for (int i = 0; i < threadsCount; ++i) {
            threads.emplace_back([&, threadIndex = i] {
                threadJob(threadIndex, threadsCount, size, current, next);
            });
        }
    }
private:
    Rules rules_;

    void threadJob(const int threadIndex, const int threadsCount, const int size, const GridState &current, GridState &next) const {
        for (int rowIndex = threadIndex; rowIndex < size; rowIndex += threadsCount) {
            for (int j = 0; j < size; j++) {
                const int index = rowIndex * size + j;
                const int aliveNeighbours = NeighboursCounter<EdgePolicy>::Count(current, rowIndex, j);
                const bool alive = current.IsCellAlive(index);
                next[index] =
                    (alive && rules_.IsNextStateStable(aliveNeighbours)) ||
                    (!alive && rules_.IsNextStateBirth(aliveNeighbours)) ? Cell::Alive : Cell::Dead;
            }
        }
    }
};
}
