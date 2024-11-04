#include "graphics/lighting/spot_light.hpp"

namespace kc {

Graphics::Lighting::SpotLight::SpotLight(const Transform& transform, const glm::vec3 direction, Color color, const LightAttenuation attenuation, const LightProperties& properties, const LightCutoff& cutoff)
    : Light(color, attenuation, properties)
    , m_cutoff(cutoff)
    , m_direction(direction)
    , m_body(transform, color, {})
{}

void Graphics::Lighting::SpotLight::draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram) const
{
    // Illuminate to shader program
    shaderProgram.set("SpotLight.color", m_color);
    shaderProgram.set("SpotLight.attenuation", m_attenuation);
    shaderProgram.set("SpotLight.cutoff", m_cutoff);
    shaderProgram.set("SpotLight.properties", m_properties);
    shaderProgram.set("SpotLight.position", m_body.transform().position);
    shaderProgram.set("SpotLight.direction", m_direction);

    // Render to light shader program
    lightShaderProgram.set("LightColor", m_color);
    m_body.draw(lightShaderProgram);
}

} // namespace kc
