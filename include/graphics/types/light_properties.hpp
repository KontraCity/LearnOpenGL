#pragma once

// Graphics libraries
#include <glm/glm.hpp>

// Custom modules
#include "graphics/types/light_attenuation.hpp"

namespace kc {

namespace Graphics
{
    struct LightProperties
    {
        float ambient = 0.2f;
        float diffuse = 0.5f;
        float specular = 1.0f;
    };
}

} // namespace kc
