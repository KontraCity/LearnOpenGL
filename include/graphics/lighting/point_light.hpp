#pragma once

// Custom modules
#include "graphics/lighting/light.hpp"
#include "graphics/cube.hpp"
#include "graphics/shader_program.hpp"

namespace kc {

    namespace Graphics
    {
        namespace Lighting
        {
            class PointLight : public Light
            {
            private:
                Cube m_body;

            public:
                /// @brief Create point light
                /// @param transform Light transform
                /// @param color Light color
                /// @param attenuation Light attenuation
                /// @param properties Light properties
                PointLight(const Transform& transform = {}, Color color = {}, const LightAttenuation attenuation = {}, const LightProperties & properties = {});

                /// @brief Draw light to the screen
                /// @param shaderProgram Shader program to illuminate
                /// @param lightShaderProgram Separate shader program to render point light
                void draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram);

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
            };
        }
    }
} // namespace kc
