#pragma once

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
}

} // namespace kc
