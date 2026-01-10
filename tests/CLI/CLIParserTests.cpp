#include <catch2/catch_test_macros.hpp>

#include "CLI/CLIOptions.h"
#include "CLI/CLIParser.h"
#include "Simulation/Factory/SimulationFactory.h"
#include "Utils/GridStateFromASCII.h"

TEST_CASE("CLI Parser Valid input") {
    {
        const char* argv[] = { "app" };
        int argc = 1;
        const auto expectedGrid = gol::DenseGrid(50);

        const auto config = gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)).MakeConfig();
        const auto sim = gol::SimulationFactory::Create(config);

        REQUIRE(sim->GetState() == expectedGrid);
    }
    {
        const char* argv[] = {
            "app",
            "--size", "5",
            "--random",
            "--seed", "42",
            "--alive-chance", "0.5",
            "--rules", "CONWAY",
            "--edges", "toroidal",
            "-t", "SingleCore"
        };
        int argc = 14;
        std::mt19937 rng(42);
        const auto expectedGrid = gol::DenseGrid::CreateRandom(5, rng, 0.5);


        const auto config = gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)).MakeConfig();
        const auto sim = gol::SimulationFactory::Create(config);

        REQUIRE(sim->GetState() == expectedGrid);
    }
    {
        const char* argv[] = {
            "app",
            "--size", "3",
            "--ascii", "...###...",
            "--rules", "conway",
            "--edges", "Toroidal"
        };
        int argc = 9;
        const auto expectedGrid = gol::GridStateFromASCII<gol::DenseGrid>(3, "...###...");


        const auto config = gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)).MakeConfig();
        const auto sim = gol::SimulationFactory::Create(config);

        REQUIRE(sim->GetState() == expectedGrid);
    }
}

TEST_CASE("CLI Parser Invalid input") {
    {
        const char* argv[] = {
            "app",
            "invalid"
        };
        int argc = 2;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::invalid_argument);
    }
    {
        const char* argv[] = {
            "app",
            "--size"
        };
        int argc = 2;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::invalid_argument);
    }
    {
        const char* argv[] = {
            "app",
            "--size", "invalid"
        };
        int argc = 3;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::invalid_argument);
    }
    {
        const char* argv[] = {
            "app",
            "--size", "123456789123456789"
        };
        int argc = 3;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::out_of_range);
    }
    {
        const char* argv[] = {
            "app",
            "--alive-chance", "invalid"
        };
        int argc = 3;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::invalid_argument);
    }
    {
        const char* argv[] = {
            "app",
            "--alive-chance", "123456789123456789123456789123456789123456789123456789.0"
        };
        int argc = 3;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::out_of_range);
    }
    {
        const char* argv[] = {
            "app",
            "--rules", "invalid",
        };
        int argc = 3;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::invalid_argument);
    }
    {
        const char* argv[] = {
            "app",
            "--size", "3",
            "--random",
            "--ascii", "...###..."
        };
        int argc = 6;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::logic_error);
    }
    {
        const char* argv[] = {
            "app",
            "--size", "3",
            "--seed", "42",
            "--ascii", "...###..."
        };
        int argc = 7;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::logic_error);
    }
    {
        const char* argv[] = {
            "app",
            "--size", "5",
            "--ascii", "...###..."
        };
        int argc = 5;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::logic_error);
    }
    {
        const char* argv[] = {
            "app",
            "--ascii", "...###...",
            "--size", "3"
        };
        int argc = 5;

        CHECK_THROWS_AS(gol::config::CLIParser::ParseArgs(argc, const_cast<char**>(argv)), std::logic_error);
    }
}