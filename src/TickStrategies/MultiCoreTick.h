#pragma once
#include "TickStrategy.h"

namespace gol {
class MultiCoreTick : public TickStrategy {
public:
    explicit MultiCoreTick(std::unique_ptr<Rules> rules);
    void Tick(const GridState &current,
              GridState &next) const override;
};
}