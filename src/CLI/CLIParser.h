#pragma once
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
        if (auto value = magic_enum::enum_cast<Enum>(val)) {
            return *value;
        }

        throw std::invalid_argument( std::string("Invalid ") + std::string(arg) + ": " + std::string(val));
    }
};
}
