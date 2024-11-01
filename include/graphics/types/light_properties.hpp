#pragma once

// Graphics libraries
#include <glm/glm.hpp>

namespace kc {

namespace Graphics
{
    struct LightProperties
    {
        float ambient = 1.0f;
        float diffuse = 1.0f;
        float specular = 1.0f;
    };
}

} // namespace kc
