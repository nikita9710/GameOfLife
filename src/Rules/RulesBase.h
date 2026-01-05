#pragma once
#include <cassert>

namespace gol::rules {
template<typename Impl>
struct RulesBase {
    [[nodiscard]] bool IsNextStateStable(int aliveNeighbours) const {
        assertValidNeighboursCount(aliveNeighbours);
        return Impl::isNextStateStableImpl(aliveNeighbours);
    }

    [[nodiscard]] bool IsNextStateBirth(int aliveNeighbours) const {
        assertValidNeighboursCount(aliveNeighbours);
        return Impl::isNextStateBirthImpl(aliveNeighbours);
    }

private:
    static void assertValidNeighboursCount(const int aliveNeighbours) {
        assert(aliveNeighbours >= 0 && aliveNeighbours <= 8);
    }
};
}
