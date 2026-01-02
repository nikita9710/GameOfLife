#pragma once
#include "TickStrategy.h"

namespace gol {
class GPUTick : public TickStrategy {
public:
    explicit GPUTick(std::unique_ptr<Rules> rules);

    void Tick(const GridState &current,
              GridState &next) const override;
};
}