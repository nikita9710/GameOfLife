#ifndef GAMEOFLIFE_GRIDSTATE_H
#define GAMEOFLIFE_GRIDSTATE_H
#include <vector>
#include <array>

#include "Common.h"

class GridState {
public:
    GridState(int size) : size_(size), state_(size_ * size_, DEAD) { }

    int& operator[](int index) { return state_[index]; }
    const int& operator[](int index) const { return state_[index]; }

    int GetNeighboringAliveCellsCount(int x, int y) const;

    bool IsCellAlive(const int index) const {
        return state_[index] == ALIVE;
    }

    bool IsCellAlive(const int x, const int y) const {
        return IsCellAlive(x*size_ + y);
    }

    int GetSize() const {
        return size_;
    }

    std::vector<int>& GetData() {
        return state_;
    }

    void Swap(GridState &other);

    void RandomizeState();
private:
    const int size_;

    std::vector<int> state_;

    struct offset {
        int dx;
        int dy;
    };

    static constexpr std::array<offset, 8> neighboursMatrix_ {{
        {-1, -1}, {-1,  0}, {-1,  1},
        { 0, -1},                      { 0,  1},
        { 1, -1}, { 1,  0}, { 1,  1}
    }};
};


#endif //GAMEOFLIFE_GRIDSTATE_H