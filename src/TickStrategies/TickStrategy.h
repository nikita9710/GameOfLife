#pragma once
#include <memory>

#include "../Simulation/GridState.h"

namespace gol {
class Rules;

class TickStrategy {
public:
    TickStrategy(std::unique_ptr<Rules> rules);
    virtual ~TickStrategy() = default;
    virtual void Tick(const GridState &current,
                      GridState &next) const = 0;
protected:
    std::unique_ptr<Rules> rules_;
};
}