#pragma once

// Graphics libraries
#include <glm/glm.hpp>

namespace kc {

namespace Graphics
{
    struct Transform
    {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
    };
}

} // namespace kc
