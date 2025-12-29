#ifndef GAMEOFLIFE_RULES_H
#define GAMEOFLIFE_RULES_H
class Rules {
public:
    virtual ~Rules() = default;

    virtual bool IsNextStateStable(int aliveNeighbours) = 0;

    virtual bool IsNextStateBirth(int aliveNeighbours) = 0;
};
#endif //GAMEOFLIFE_RULES_H