#pragma once

// STL modules
#include <random>

// Library spdlog
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace kc {

namespace Utility
{
    /// @brief Create logger
    /// @param name Logger name
    /// @return Created logger
    spdlog::logger CreateLogger(const std::string& name);

    /// @brief Limit value to an inclusive range
    /// @param value The value to limit
    /// @param min Minimum range bound
    /// @param max Maximum range bound
    /// @return Limited value
    double Limit(double value, double min, double max);

    /// @brief Generate random integer
    /// @param min Min integer value
    /// @param max Max integer value
    /// @return Generated integer
    int Random(int min, int max);

    /// @brief Generate random real
    /// @param min Min real value
    /// @param max Max real value
    /// @return Generated real
    double Random(double min, double max);
}

} // namespace kc
