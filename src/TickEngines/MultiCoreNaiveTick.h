#pragma once
#include <cassert>
#include <thread>

#include "RowProcessor.h"

namespace gol {
template<typename EdgePolicy, typename Rules>
class MultiCoreNaiveTick {
public:
    void Tick(const GridState &current, GridState &next) const {
        const int size = current.GetSize();
        const int threadsCount = std::min(MaxThreadsCount, size);

        std::vector<std::jthread> threads;
        threads.reserve(threadsCount);

        const int rowsPerThread = (size + threadsCount - 1) / threadsCount;

        for (int i = 0; i < threadsCount; ++i) {
            threads.emplace_back([&, threadIndex = i] {
                threadJob(threadIndex*rowsPerThread, std::min(size, (threadIndex+1)*rowsPerThread), size, current, next);
            });
        }
    }
private:
    Rules rules_;

    void threadJob(const int startRowIndex, const int lastRowIndex, const int size, const GridState &current, GridState &next) const {
        for (int rowIndex = startRowIndex; rowIndex < lastRowIndex; rowIndex++) {
            RowProcessor<EdgePolicy, Rules>::compute(rowIndex, size, rules_, current, next);
        }
    }
};
}
