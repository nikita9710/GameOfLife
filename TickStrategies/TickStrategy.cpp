#include "TickStrategy.h"
#include "../Rules/Rules.h"

#include <algorithm>

TickStrategy::TickStrategy(std::unique_ptr<Rules> rules): rules_(std::move(rules)) {}
