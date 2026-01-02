#pragma once
#include <cassert>

namespace gol {
class Rules {
public:
    virtual ~Rules() = default;

    bool IsNextStateStable(int aliveNeighbours) {
        assertValidNeighboursCount(aliveNeighbours);
        return isNextStateStableImpl(aliveNeighbours);
    }

    bool IsNextStateBirth(int aliveNeighbours) {
        assertValidNeighboursCount(aliveNeighbours);
        return isNextStateBirthImpl(aliveNeighbours);
    }

protected:
    virtual bool isNextStateStableImpl(int aliveNeighbours) = 0;

    virtual bool isNextStateBirthImpl(int aliveNeighbours) = 0;

    static void assertValidNeighboursCount(const int aliveNeighbours) {
        assert(aliveNeighbours >= 0 && aliveNeighbours < 9);
    }
};
}
