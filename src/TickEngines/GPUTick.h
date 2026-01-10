#pragma once
#include <cassert>

namespace gol {
template<typename Grid, typename EdgePolicy, typename Rules>
class GPUTick{
public:
    void Tick(const Grid &current, Grid &next) const {
        assert(false && "Not implemented");
    }
private:
    Rules rules_;
};
}