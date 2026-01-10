#pragma once
#include <cassert>

namespace gol {
template<typename Grid, typename EdgePolicy>
struct NeighboursCounter {
    [[nodiscard]] static int Count(const Grid &currentState, int x, int y) {
        const auto size = currentState.GetSize();
        assert(x >= 0 && x < size && y >= 0 && y < size);

        int res = 0;

        for (const auto&[dx, dy]: neighboursMatrix_) {
            int nx, ny;
            if (EdgePolicy::resolve(x, y, dx, dy, size, nx, ny)) {
                res += currentState.IsCellAlive(nx * size + ny);
            }
        }

        return res;
    }

    struct offset {
        int dx;
        int dy;
    };

    static constexpr std::array<offset, 8> neighboursMatrix_ {{
        {-1, -1}, {-1,  0}, {-1,  1},
        { 0, -1},           { 0,  1},
        { 1, -1}, { 1,  0}, { 1,  1}
    }};
};


}
