#include "graphics/light.hpp"

namespace kc {

Graphics::Light::Light()
    : Light({}, {}, {})
{}

Graphics::Light::Light(const Transform& transform, Color color, const LightProperties& properties)
    : Cube(transform, color, {})
    , m_properties(properties)
{}

void Graphics::Light::draw(ShaderProgram& shaderProgram, ShaderProgram& lightShaderProgram) const
{
    draw(lightShaderProgram);
    shaderProgram.set("LightPosition", m_transform.position);
    shaderProgram.set("LightColor", m_color);
    shaderProgram.set("LightProperties", m_properties);
    lightShaderProgram.set("LightColor", m_color);
}

} // namespace kc
