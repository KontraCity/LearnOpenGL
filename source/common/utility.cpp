#include "common/utility.hpp"

namespace kc {

double Utility::Limit(double value, double min, double max)
{
    if (value < min)
        value = min;
    if (value > max)
        value = max;
    return value;
}

} // namespace kc
