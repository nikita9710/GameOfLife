#pragma once
#include "TickStrategy.h"

namespace gol {
template<typename EdgePolicy>
class MultiCoreTick : public TickStrategy<EdgePolicy> {
public:
    explicit MultiCoreTick(std::unique_ptr<Rules> rules) : TickStrategy<EdgePolicy>(std::move(rules)) { }

    void Tick(const GridState &current, GridState &next) const override {
        assert(false && "Not implemented");
    }
};
}