#pragma once

// Graphics libraries
#include <glm/glm.hpp>

// Custom modules
#include "graphics/lighting/light.hpp"
#include "graphics/types/light_cutoff.hpp"
#include "graphics/cube.hpp"
#include "graphics/shader_program.hpp"

namespace kc {

namespace Graphics
{
    namespace Lighting
    {
        class SpotLight : public Light
        {
        private:
            LightCutoff m_cutoff;
            glm::vec3 m_direction;
            Cube m_body;

        private:
            using Light::attenuation;

        public:
            /// @brief Create spot light
            /// @param transform Light transform
            /// @param direction Light direction
            /// @param color Light color
            /// @param attenuation Light attenuation
            /// @param properties Light properties
            /// @param cutoff Light cutoff
            SpotLight(const Transform& transform = {}, const glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), Color color = {}, const LightAttenuation attenuation = {}, const LightProperties& properties = {}, const LightCutoff& cutoff = {});

            /// @brief Draw light to the screen
            /// @param shaderProgram Shader program to illuminate
            /// @param lightShaderProgram Separate shader program to render point light
            void draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram) const;

            /// @brief Get light transform
                /// @return Light transform
            inline const Transform& transform() const
            {
                return m_body.transform();
            }

            /// @brief Get light transform
            /// @return Light transform
            inline Transform& transform()
            {
                return m_body.transform();
            }

            /// @brief Get light cutoff
            /// @return Light cutoff
            inline LightCutoff cutoff() const
            {
                return m_cutoff;
            }

            /// @brief Get light cutoff
            /// @return Light cutoff
            inline LightCutoff& cutoff()
            {
                return m_cutoff;
            }

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
