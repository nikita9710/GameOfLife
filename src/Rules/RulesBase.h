#pragma once
#include <cassert>

namespace gol {
template<typename Impl>
struct RulesBase {
    bool IsNextStateStable(int aliveNeighbours) const {
        assertValidNeighboursCount(aliveNeighbours);
        return Impl::isNextStateStableImpl(aliveNeighbours);
    }

    bool IsNextStateBirth(int aliveNeighbours) const {
        assertValidNeighboursCount(aliveNeighbours);
        return Impl::isNextStateBirthImpl(aliveNeighbours);
    }

private:
    static void assertValidNeighboursCount(const int aliveNeighbours) {
        assert(aliveNeighbours >= 0 && aliveNeighbours <= 8);
    }
};
}
