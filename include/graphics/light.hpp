#pragma once

// Custom modules
#include "graphics/cube.hpp"

namespace kc {

namespace Graphics
{
    class Light : public Cube
    {
    private:
        glm::vec3 m_properties;

    private:
        using Cube::draw;

    public:
        /// @brief Crate light
        Light();

        /// @brief Crate light
        /// @param transform Light transform
        /// @parma color Light color
        /// @param properties Light properties
        Light(const Transform& transform, Color color, const glm::vec3& properties);

        /// @brief Draw light to the screen
        /// @param shaderProgram Shader program to configure for lighting
        /// @param shaderProgram Shader program to draw the light with
        void draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram) const;

        /// @brief Get light properties
        /// @return Light properties
        inline const glm::vec3& properties() const
        {
            return m_properties;
        }

        /// @brief Get light properties
        /// @return Light properties
        inline glm::vec3& properties()
        {
            return m_properties;
        }
    };
}

} // namespace kc
