#include "graphics/lighting/point_light.hpp"

namespace kc {

Graphics::Lighting::PointLight::PointLight(const Transform& transform, Color color, const LightAttenuation attenuation, const LightProperties& properties)
    : Light(color, attenuation, properties)
    , m_body(transform, color, {})
{}

void Graphics::Lighting::PointLight::draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram)
{
    // Illuminate to shader program
    shaderProgram.set("PointLight.color", m_color);
    shaderProgram.set("PointLight.attenuation", m_attenuation);
    shaderProgram.set("PointLight.properties", m_properties);
    shaderProgram.set("PointLight.position", m_body.transform().position);

    // Render to light shader program
    lightShaderProgram.set("LightColor", m_color);
    m_body.draw(lightShaderProgram);
}

} // namespace kc
