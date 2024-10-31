#pragma once

// Graphics libraries
#include <GL/glew.h>

// Custom libraries
#include "graphics/shader_program.hpp"
#include "graphics/transform.hpp"

namespace kc {

namespace Graphics
{
    class Cube : public Transform
    {
    private:
        unsigned int m_vertexArrayObject;
        unsigned int m_vertexBufferObject;
        unsigned int m_elementBufferObject;

    public:
        Cube();

        ~Cube();

        /// @brief Create cube
        /// @param position Transform position
        /// @param rotation Transform rotation
        /// @param scale Transform scale
        void create(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));

        /// @brief Draw cube to the screen
        /// @param shaderProgram Shader program to draw with
        void draw(ShaderProgram& shaderProgram) const;
    };
}

} // namespace kc
