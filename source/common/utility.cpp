#include "common/utility.hpp"

namespace kc {

spdlog::logger Utility::CreateLogger(const std::string& name)
{
    static auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    static bool initialized = false;
    if (!initialized)
    {
        sink->set_pattern("[%^%d.%m.%C %H:%M:%S %L%$] [%n] %v");
        initialized = true;
    }
    return { name, {sink} };
}

double Utility::Limit(double value, double min, double max)
{
    if (value < min)
        value = min;
    if (value > max)
        value = max;
    return value;
}

} // namespace kc
