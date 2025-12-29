#include "Grid.h"
#include <algorithm>
#include <iostream>


void Grid::Tick() {
    strategy_->Tick(currentState_, nextState_);
    currentState_.Swap(nextState_);
}