#include "CLIParser.h"

#include <charconv>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string_view>

#include "CLIOptions.h"
#include "Utils/GridStateFromASCII.h"

namespace gol::config {
CLIOptions CLIParser::ParseArgs(const int argc, char **argv) {
    CLIOptions res;
    bool sizeParsed = false;
    for (int i = 1; i < argc; ++i) {
        const std::string_view arg = argv[i];

        if (arg == "--size" || arg == "-s") {
            requireValue(i, argc, argv);
            res.size_ = parseInt(argv[++i]);
            sizeParsed = true;
        }
        else if (arg == "--edges" || arg == "-e") {
            requireValue(i, argc, argv);
            res.edgeMode_ = parseEnum<EdgeMode>(arg, argv[++i]);
        }
        else if (arg == "--rules" || arg == "-r") {
            requireValue(i, argc, argv);
            res.ruleset_ = parseEnum<Ruleset>(arg, argv[++i]);
        }
        else if (arg == "--tick" || arg == "-t") {
            requireValue(i, argc, argv);
            res.tickMode_ = parseEnum<TickMode>(arg, argv[++i]);
        }
        else if (arg == "--random") {
            if (res.initialState_ == InitialState::Predefined) {
                throw std::invalid_argument("Conflicting params combination - random and predefined");
            }
            if (res.initialState_ == InitialState::RandomSeeded) {
                continue;
            }
            res.initialState_ = InitialState::Random;
        }
        else if (arg == "--seed") {
            if (res.initialState_ == InitialState::Predefined) {
                throw std::invalid_argument("Conflicting params combination - random and predefined");
            }
            requireValue(i, argc, argv);
            res.initialState_ = InitialState::RandomSeeded;
            res.seed_ = parseInt(argv[++i]);
        }
        else if (arg == "--predefined-ascii" || arg == "--ascii") {
            if (res.initialState_ == InitialState::Random || res.initialState_ == InitialState::RandomSeeded) {
                throw std::invalid_argument("Conflicting params combination - random and predefined");
            }
            if (!sizeParsed) {
                throw std::invalid_argument("Grid size argument must be preceding predefined state");
            }
            requireValue(i, argc, argv);
            res.initialState_ = InitialState::Predefined;
            res.predefinedState_.emplace(GridStateFromASCII(argv[++i], res.size_));
        }
        else if (arg == "--alive-chance" || arg == "-a") {
            requireValue(i, argc, argv);
            res.aliveChance_ = parseFloat(argv[++i]);
        }
        else {
            throw std::invalid_argument("Unknown cli argument: " + std::string(arg));
        }
    }

    return res;
}

int CLIParser::parseInt(std::string_view str) {
    int value{};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

    if (ec == std::errc::invalid_argument || ptr != str.data() + str.size()) {
        throw std::invalid_argument("Invalid integer: " + std::string(str));
    }
    if (ec == std::errc::result_out_of_range) {
        throw std::out_of_range("Integer out of range: " + std::string(str));
    }
    return value;
}

float CLIParser::parseFloat(std::string_view str) {
    float value{};
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

    if (ec == std::errc::invalid_argument || ptr != str.data() + str.size()) {
        throw std::invalid_argument("Invalid float: " + std::string(str));
    }
    if (ec == std::errc::result_out_of_range) {
        throw std::out_of_range("Float out of range: " + std::string(str));
    }
    return value;
}

void CLIParser::requireValue(const int i, const int argc, char **argv) {
    if (i + 1 == argc || argv[i + 1][0] == '-') {
        throw std::invalid_argument("Missing value for option: " + std::string(argv[i]));
    }
}
}
