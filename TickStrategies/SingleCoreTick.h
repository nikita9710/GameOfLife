#ifndef GAMEOFLIFE_SINGLECORETICK_H
#define GAMEOFLIFE_SINGLECORETICK_H
#include "TickStrategy.h"


class SingleCoreTick : public TickStrategy {
public:
    explicit SingleCoreTick(std::unique_ptr<Rules> rules);

    void Tick(const GridState &current,
              GridState &next) override;

};

#endif //GAMEOFLIFE_SINGLECORETICK_H