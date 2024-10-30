#pragma once

// STL modules
#include <chrono>

namespace kc {

class Stopwatch
{
private:
    using clock = std::chrono::high_resolution_clock;
    clock::time_point m_start;

public:
    /// @brief Initialize and start stopwatch
    Stopwatch()
        : m_start(clock::now())
    {}

    /// @brief Reset stopwatch
    inline void reset()
    {
        m_start = clock::now();
    }

    /// @brief Get elapsed time in seconds
    /// @return Elapsed time in seconds
    inline float seconds() const
    {
        return milliseconds() / 1000.0;
    }

    /// @brief Get elapsed time in milliseconds
    /// @return Elapsed time in milliseconds
    inline size_t milliseconds() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_start).count();
    }
};

} // namespace kc
