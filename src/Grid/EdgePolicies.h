#pragma once

namespace gol {
struct ToroidalEdgePolicy {
    static constexpr bool wrapsHorizontally = true;
    static constexpr bool wrapsVertically = true;

    [[nodiscard]] static bool resolveDenseCell(const int x, const int y, const int dx, const int dy, const int size, int& outX, int& outY) {
        //toroidal wrapping => bottom row considered a neighbour of top row, same for right/left
        outX = (x + dx + size) % size;
        outY = (y + dy + size) % size;
        return true;
    }

    [[nodiscard]] static bool resolveTopWordRow(const int row, const int wordsPerRow, const size_t dataSize, size_t& outIndex) {
        outIndex = (row == 0 ? (dataSize - wordsPerRow) : wordsPerRow*(row - 1));
        return true;
    }

    [[nodiscard]] static bool resolveBottomWordRow(const int row, const int wordsPerRow, const int gridSize, size_t& outIndex) {
        outIndex = (row == gridSize - 1 ? (wordsPerRow * 0) : wordsPerRow*(row + 1));
        return true;
    }
};

struct ClampedEdgePolicy {
    static constexpr bool wrapsHorizontally = false;
    static constexpr bool wrapsVertically = false;

    [[nodiscard]] static bool resolveDenseCell(const int x, const int y, const int dx, const int dy, const int size, int& outX, int& outY) {
        if (x + dx < 0 || y + dy < 0 || x + dx > size-1 || y + dy > size-1) {
            return false;
        }
        outX = x + dx;
        outY = y + dy;
        return true;
    }

    [[nodiscard]] static bool resolveTopWordRow(const int row, const int wordsPerRow, const size_t dataSize, size_t& outIndex) {
        if (row == 0)
            return false;
        outIndex = wordsPerRow*(row - 1);
        return true;
    }

    [[nodiscard]] static bool resolveBottomWordRow(const int row, const int wordsPerRow, const int gridSize, size_t& outIndex) {
        if (row == gridSize - 1)
            return false;
        outIndex = wordsPerRow*(row + 1);
        return true;
    }
};
}
