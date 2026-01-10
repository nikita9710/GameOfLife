#pragma once

namespace gol::config {
enum class TickMode {
    SingleCore,
    MultiCoreNaive,
    MultiCorePool,
};
}