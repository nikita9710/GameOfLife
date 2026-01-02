#pragma once
#include "TickStrategy.h"

namespace gol {
class SingleCoreTick : public TickStrategy {
public:
    explicit SingleCoreTick(std::unique_ptr<Rules> rules);

    void Tick(const GridState &current,
              GridState &next) const override;

};
}