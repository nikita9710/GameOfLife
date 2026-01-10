#pragma once
#include <barrier>
#include <cassert>
#include <condition_variable>
#include <thread>

#include "RowProcessor.h"

namespace gol {
template<typename EdgePolicy, typename Rules>
class MultiCorePoolTick {
public:
    MultiCorePoolTick() : mainBarrier(MaxThreadsCount + 1),
            workerBarrier(MaxThreadsCount + 1)  {
        threads_.reserve(MaxThreadsCount);
        for (int i = 0; i < MaxThreadsCount; ++i) {
            threads_.emplace_back([&] {
                threadJob();
            });
        }
    }

    ~MultiCorePoolTick() {
        {
            std::lock_guard lock(mutex_);
            alive_ = false;
        }
        mainBarrier.arrive_and_drop();
        workerBarrier.arrive_and_drop();
        cv_.notify_all();
    }

    void Tick(const GridState &current, GridState &next) const {
        {
            std::unique_lock lock(mutex_);
            jobContext_.size = current.GetSize();
            jobContext_.current = &current;
            jobContext_.next = &next;
            jobContext_.nextRowIndex = 0;

            jobContext_.ready = true;
        }
        cv_.notify_all();

        mainBarrier.arrive_and_wait();

        {
            std::unique_lock lock(mutex_);
            jobContext_.ready = false;
        }

        workerBarrier.arrive_and_wait();
    }
private:
    Rules rules_;
    struct JobContext {
        constexpr static int chunkSize = 16;
        int size = 0;
        const GridState *current = nullptr;
        GridState *next = nullptr;
        bool ready = false;

        alignas(64) std::atomic<int> nextRowIndex = 0;
    };
    mutable JobContext jobContext_;
    std::vector<std::jthread> threads_;
    mutable std::condition_variable cv_;
    mutable std::mutex mutex_;
    std::atomic<bool> alive_ = true;

    mutable std::barrier<> mainBarrier;

    mutable std::barrier<> workerBarrier;

    void threadJob() {
        while (alive_) {
            {
                std::unique_lock lock(mutex_);
                cv_.wait(lock, [&] {
                    return jobContext_.ready || !alive_;
                });

                if (!alive_)
                    return;
            }

            const auto size = jobContext_.size;
            while (true) {
                const int rowStart = jobContext_.nextRowIndex.fetch_add(JobContext::chunkSize, std::memory_order_relaxed);
                if (rowStart >= size)
                    break;
                computeChunk(rowStart, std::min(rowStart + JobContext::chunkSize, size), size, *jobContext_.current, *jobContext_.next);
            }

            mainBarrier.arrive_and_wait();

            workerBarrier.arrive_and_wait();
        }
    }

    void computeChunk(const int startRowIndex, const int lastRowIndex, const int size, const GridState &current, GridState &next) {
        for (int rowIndex = startRowIndex; rowIndex < lastRowIndex; rowIndex++) {
            RowProcessor<EdgePolicy, Rules>::compute(rowIndex, size, rules_, current, next);
        }
    }
};
}
