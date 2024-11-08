#pragma once

// Custom modules
#include "graphics/texture.hpp"

namespace kc {

namespace Graphics
{
    struct Material
    {
        Texture::Pointer diffuse;
        Texture::Pointer specular;
        float shininess = 32.0f;
    };
}

} // namespace kc
