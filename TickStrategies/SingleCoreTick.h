#ifndef GAMEOFLIFE_SINGLECORETICK_H
#define GAMEOFLIFE_SINGLECORETICK_H
#include "TickStrategy.h"


class SingleCoreTick : public TickStrategy {
    void Tick(const GridState &current,
              GridState &next) override;

};

#endif //GAMEOFLIFE_SINGLECORETICK_H