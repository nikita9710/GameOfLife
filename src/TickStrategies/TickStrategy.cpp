#include "TickStrategy.h"
#include "../Rules/Rules.h"

#include <algorithm>

namespace gol {
TickStrategy::TickStrategy(std::unique_ptr<Rules> rules): rules_(std::move(rules)) {}
}