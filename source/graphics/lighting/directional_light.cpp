#include "graphics/lighting/directional_light.hpp"

namespace kc {

Graphics::Lighting::DirectionalLight::DirectionalLight(const glm::vec3 direction, Color color, const LightProperties& properties)
    : Light(color, {}, properties)
    , m_direction(direction)
{}

void Graphics::Lighting::DirectionalLight::draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram)
{
    // Illuminate to shader program
    shaderProgram.set("DirectionalLight.color", m_color);
    shaderProgram.set("DirectionalLight.properties", m_properties);
    shaderProgram.set("DirectionalLight.direction", m_direction);

    // Render to light shader program
    lightShaderProgram.set("LightColor", m_color);
    m_body.transform().position = m_direction * -50.0f;
    m_body.draw(lightShaderProgram);
}

} // namespace kc
