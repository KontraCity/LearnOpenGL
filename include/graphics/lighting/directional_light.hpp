#pragma once

// Graphics libraries
#include <glm/glm.hpp>

// Custom modules
#include "graphics/lighting/light.hpp"
#include "graphics/cube.hpp"
#include "graphics/shader_program.hpp"

namespace kc {

namespace Graphics
{
    namespace Lighting
    {
        class DirectionalLight : public Light
        {
        private:
            glm::vec3 m_direction;
            Cube m_body;

        private:
            using Light::attenuation;

        public:
            /// @brief Create directional light
            /// @param direction Light direction
            /// @param color Light color
            /// @param properties Light properties
            DirectionalLight(const glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), Color color = {}, const LightProperties& properties = {});

            /// @brief Draw light to the screen
            /// @param shaderProgram Shader program to illuminate
            /// @param lightShaderProgram Separate shader program to render point light
            void draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram);

            /// @brief Get light direction
            /// @return Light direction
            inline const glm::vec3& direction() const
            {
                return m_direction;
            }

            /// @brief Get light direction
            /// @return Light direction
            inline glm::vec3& direction()
            {
                return m_direction;
            }
        };
    }
}

} // namespace kc
