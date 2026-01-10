#include <iostream>
#include <thread>
#include <chrono>

#include "CLI/CLIOptions.h"
#include "CLI/CLIParser.h"
#include "Config/SimulationConfig.h"
#include "Printers/ConsolePrinter.h"
#include "Simulation/Factory/SimulationFactory.h"

int main(int argc, char** argv) {
    using namespace gol;
    if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
        // todo
        std::cout << "todo help" << std::endl;
        return 0;
    }
    const auto simConfig = config::CLIParser::ParseArgs(argc, argv).MakeConfig();
    const auto simulation = SimulationFactory::Create(simConfig);
    const std::unique_ptr<Printer> printer = std::make_unique<ConsolePrinter>();
    int numTicks = 0;
    double totalFrameTime = 0.0;
    while (true) {
        auto timeBeforeTick = std::chrono::system_clock::now();
        simulation->Tick();
        const auto timeAfterTick = std::chrono::system_clock::now();
        printer->PrintGrid(simulation->GetState());
        const auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(timeAfterTick - timeBeforeTick).count()/1000.0;
        totalFrameTime += frameTime;
        printer->PrintStats(frameTime, totalFrameTime/numTicks);
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        numTicks++;
    }

    return 0;
}
