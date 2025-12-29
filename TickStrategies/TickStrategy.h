#ifndef GAMEOFLIFE_TICKSTRATEGY_H
#define GAMEOFLIFE_TICKSTRATEGY_H
#include "../GridState.h"

class TickStrategy {
    public:
    virtual ~TickStrategy() = default;
    virtual void Tick(const GridState &current,
                      GridState &next) = 0;
protected:
    static constexpr int stableRule_[]{2, 3};

    static constexpr int birthRule_[]{3};

    static bool isNextStateStable(int aliveNeighbours) {
        return std::ranges::find(stableRule_, aliveNeighbours) != std::end(stableRule_);
    }

    static bool isNextStateBirth(int aliveNeighbours) {
        return std::ranges::find(birthRule_, aliveNeighbours) != std::end(birthRule_);
    }
};
#endif //GAMEOFLIFE_TICKSTRATEGY_H