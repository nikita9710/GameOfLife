#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H
#include <memory>

#include "GridState.h"

class TickStrategy;

class Simulation {
public:
    Simulation(int size, std::unique_ptr<TickStrategy> strategy);

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