//
// Created by nikita on 12/29/25.
//

#ifndef GAMEOFLIFE_MULTICORETICK_H
#define GAMEOFLIFE_MULTICORETICK_H
#include "TickStrategy.h"


class MultiCoreTick : public TickStrategy {
public:
    explicit MultiCoreTick(std::unique_ptr<Rules> rules);
    void Tick(const GridState &current,
              GridState &next) override;
};


#endif //GAMEOFLIFE_MULTICORETICK_H