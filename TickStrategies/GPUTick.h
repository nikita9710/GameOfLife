//
// Created by nikita on 12/29/25.
//

#ifndef GAMEOFLIFE_GPUTICK_H
#define GAMEOFLIFE_GPUTICK_H
#include "TickStrategy.h"


class GPUTick : public TickStrategy {
    void Tick(const GridState &current,
              GridState &next) override;
};


#endif //GAMEOFLIFE_GPUTICK_H