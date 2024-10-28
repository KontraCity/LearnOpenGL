#pragma once

namespace kc {

namespace Utility
{
    /// @brief Limit value to an inclusive range
    /// @param value The value to limit
    /// @param min Minimum range bound
    /// @param max Maximum range bound
    /// @return Limited value
    double Limit(double value, double min, double max);
}

} // namespace kc
