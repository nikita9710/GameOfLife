#pragma once
#include "RowProcessor.h"
#include "../Grid/NeighboursCounter.h"

namespace gol {
template<typename Grid, typename EdgePolicy, typename Rules>
class SingleCoreTick {
public:
    void Tick(const Grid &current, Grid &next) const {
        const int size = current.GetSize();
        for (int i = 0; i < size; i++) {
            RowProcessor<Grid, EdgePolicy, Rules>::compute(i, size, rules_, current, next);
        }
    }
private:
    Rules rules_;
};
}
