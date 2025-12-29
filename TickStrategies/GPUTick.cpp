#include "GPUTick.h"
#include "../Rules/Rules.h"

GPUTick::GPUTick(std::unique_ptr<Rules> rules): TickStrategy(std::move(rules)) { }

void GPUTick::Tick(const GridState &current, GridState &next) {
    throw std::exception();
}
