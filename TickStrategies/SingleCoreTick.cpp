#include "SingleCoreTick.h"

void SingleCoreTick::Tick(const GridState &current, GridState &next) {
    int size = current.GetSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            const int index = i * size + j;
            const int aliveNeighbours = current.GetNeighboringAliveCellsCount(i, j);
            const bool alive = current.IsCellAlive(index);
            next.GetData()[index] =
                (alive && isNextStateStable(aliveNeighbours)) ||
                (!alive && isNextStateBirth(aliveNeighbours)) ? ALIVE : DEAD;
        }
    }
}
