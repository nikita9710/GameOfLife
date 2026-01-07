#pragma once
#include <algorithm>
#include <stdexcept>
#include <string_view>

#include "Utils/magic_enum.hpp"

namespace gol::config {
struct CLIOptions;

class CLIParser {
public:
    static CLIOptions ParseArgs(int argc, char** argv);

private:
    static void requireValue(int i, int argc, char** argv);

    static int parseInt(std::string_view str);

    static float parseFloat(std::string_view str);

    template<typename Enum>
    static Enum parseEnum(const std::string_view arg, const std::string_view val) {
        std::string normalized(val);
        std::ranges::transform(normalized, normalized.begin(),
                                [](unsigned char c) { return std::tolower(c); });

        for (auto e : magic_enum::enum_values<Enum>()) {
            std::string name(magic_enum::enum_name(e));
            std::ranges::transform(name, name.begin(),
                                    [](unsigned char c) { return std::tolower(c); });

            if (name == normalized) {
                return e;
            }
        }

        throw std::invalid_argument(
            std::string("Invalid ") + std::string(arg) + ": " + std::string(val));
    }
};
}
