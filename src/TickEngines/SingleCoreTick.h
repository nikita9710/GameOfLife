#pragma once
#include "RowProcessor.h"
#include "../Grid/NeighboursCounter.h"

namespace gol {
template<typename EdgePolicy, typename Rules>
class SingleCoreTick {
public:
    void Tick(const GridState &current, GridState &next) const {
        const int size = current.GetSize();
        for (int i = 0; i < size; i++) {
            RowProcessor<EdgePolicy, Rules>::compute(i, size, rules_, current, next);
        }
    }
private:
    Rules rules_;
};
}
