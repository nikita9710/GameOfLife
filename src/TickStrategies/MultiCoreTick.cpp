#include "MultiCoreTick.h"

#include <cassert>

#include "../Rules/Rules.h"

namespace gol {
MultiCoreTick::MultiCoreTick(std::unique_ptr<Rules> rules) : TickStrategy(std::move(rules)) { }

void MultiCoreTick::Tick(const GridState &current, GridState &next) const {
    assert(false && "Not implemented");
}
}