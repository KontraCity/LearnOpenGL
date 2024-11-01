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
        float innerCutoff = 15.0f;
        float outerCutoff = 20.0f;
        float ambient = 1.0f;
        float diffuse = 1.0f;
        float specular = 1.0f;
        LightAttenuation attenuation;
    };
}

} // namespace kc
