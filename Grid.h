#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H
#include <memory>

#include "GridState.h"
#include "TickStrategies/TickStrategy.h"

class Grid {
public:
    Grid(const int size, std::unique_ptr<TickStrategy> strategy) : currentState_(size), nextState_(size){
        strategy_ = std::move(strategy);
        currentState_.RandomizeState();
    }
    void Tick();

    const GridState& GetState() const {
        return currentState_;
    }
private:
    std::unique_ptr<TickStrategy> strategy_;

    GridState currentState_;

    GridState nextState_;
};


#endif //GAMEOFLIFE_GRID_H