#pragma once

namespace gol {
struct ToroidalEdgePolicy {
    static bool resolve(const int x, const int y, const int dx, const int dy, const int size, int& outX, int& outY) {
        //toroidal wrapping => bottom row considered a neighbour of top row, same for right/left
        outX = (x + dx + size) % size;
        outY = (y + dy + size) % size;
        return true;
    }
};

struct ClampedEdgePolicy {
    static bool resolve(const int x, const int y, const int dx, const int dy, const int size, int& outX, int& outY) {
        if (x + dx < 0 || y + dy < 0 || x + dx > size-1 || y + dy > size-1) {
            return false;
        }
        outX = x + dx;
        outY = y + dy;
        return true;
    }
};
}