#pragma once

// Custom modules
#include "graphics/types/light_properties.hpp"
#include "graphics/cube.hpp"

namespace kc {

namespace Graphics
{
    class Light : public Cube
    {
    private:
        LightProperties m_properties;

    private:
        using Cube::draw;

    public:
        /// @brief Crate light
        Light();

        /// @brief Crate light
        /// @param transform Light transform
        /// @parma color Light color
        /// @param properties Light properties
        Light(const Transform& transform, Color color, const LightProperties& properties);

        /// @brief Draw light to the screen
        /// @param shaderProgram Shader program to configure for lighting
        /// @param shaderProgram Shader program to draw the light with
        void draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram) const;

        /// @brief Get light properties
        /// @return Light properties
        inline const LightProperties& properties() const
        {
            return m_properties;
        }

        /// @brief Get light properties
        /// @return Light properties
        inline LightProperties& properties()
        {
            return m_properties;
        }
    };
}

} // namespace kc
