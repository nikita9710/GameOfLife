#ifndef GAMEOFLIFE_TICKSTRATEGY_H
#define GAMEOFLIFE_TICKSTRATEGY_H

#include <memory>

#include "../Simulation/GridState.h"

class Rules;

class TickStrategy {
public:
    TickStrategy(std::unique_ptr<Rules> rules);;
    virtual ~TickStrategy() = default;
    virtual void Tick(const GridState &current,
                      GridState &next) = 0;
protected:
    std::unique_ptr<Rules> rules_;
};
#endif //GAMEOFLIFE_TICKSTRATEGY_H