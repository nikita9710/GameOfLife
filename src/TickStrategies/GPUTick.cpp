#include "GPUTick.h"

#include <cassert>

#include "../Rules/Rules.h"

namespace gol {
GPUTick::GPUTick(std::unique_ptr<Rules> rules): TickStrategy(std::move(rules)) { }

void GPUTick::Tick(const GridState &current, GridState &next) {
    assert(false && "Not implemented");
}
}