#pragma once

namespace gol {
class Rules {
public:
    virtual ~Rules() = default;

    virtual bool IsNextStateStable(int aliveNeighbours) = 0;

    virtual bool IsNextStateBirth(int aliveNeighbours) = 0;
};
}