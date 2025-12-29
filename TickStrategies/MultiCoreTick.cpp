#include "MultiCoreTick.h"
#include "../Rules/Rules.h"

MultiCoreTick::MultiCoreTick(std::unique_ptr<Rules> rules) : TickStrategy(std::move(rules)) { }

void MultiCoreTick::Tick(const GridState &current, GridState &next) {
    throw std::exception();
}
