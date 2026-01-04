#pragma once
#include <cassert>

namespace gol {
template<typename EdgePolicy, typename Rules>
class MultiCoreTick {
public:
    void Tick(const GridState &current, GridState &next) const {
        assert(false && "Not implemented");
    }
};
}