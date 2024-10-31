#include "graphics/camera.hpp"
using namespace kc::Graphics::CameraConst;

namespace kc {

float Graphics::Camera::MovementModeToSpeed(MovementMode mode)
{
    switch (mode)
    {
        default:
        case MovementMode::Normal:
            return Speed::Normal;
        case MovementMode::Fast:
            return Speed::Fast;
        case MovementMode::Slow:
            return Speed::Slow;
    }
}

Graphics::Camera::Camera()
{
    resetPosition();
}

void Graphics::Camera::resetPosition()
{
    m_position = glm::vec3(0.0f, 0.0f, 3.0f);
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_yaw = -90.0f;
    m_pitch = 0.0f;
    m_zoom = 1.0f;
}

void Graphics::Camera::resetZoom()
{
    m_zoom = 1.0f;
}

void Graphics::Camera::keyPressed(Key key, MovementMode movementMode, float deltaTime)
{
    switch (key)
    {
        case Key::Up:
            m_position.y += MovementModeToSpeed(movementMode) * deltaTime;
            break;
        case Key::Down:
            m_position.y -= MovementModeToSpeed(movementMode) * deltaTime;
            break;
        case Key::Forward:
            m_position += m_front * MovementModeToSpeed(movementMode) * deltaTime;
            break;
        case Key::Backward:
            m_position -= m_front * MovementModeToSpeed(movementMode) * deltaTime;
            break;
        case Key::Left:
            m_position -= glm::normalize(glm::cross(m_front, m_up)) * MovementModeToSpeed(movementMode) * deltaTime;
            break;
        case Key::Right:
            m_position += glm::normalize(glm::cross(m_front, m_up)) * MovementModeToSpeed(movementMode) * deltaTime;
            break;
    }
}

void Graphics::Camera::mouseMoved(int xOffset, int yOffset)
{
    m_yaw += xOffset * Sensivity::Move;
    m_pitch = Utility::Limit(m_pitch + yOffset * Sensivity::Move / m_zoom, Pitch::Min, Pitch::Max);
}

void Graphics::Camera::mouseScrolled(int offset)
{
    m_zoom = Utility::Limit(m_zoom += offset * Sensivity::Scroll * m_zoom, Zoom::Min, Zoom::Max);
}

void Graphics::Camera::capture(const std::vector<std::reference_wrapper<ShaderProgram>>& shaderPrograms, unsigned int width, unsigned int height)
{
    glm::vec3 direction(
        std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch)),
        std::sin(glm::radians(m_pitch)),
        std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch))
    );
    m_front = glm::normalize(direction);

    glm::mat4 view(1.0f), projection(1.0f);
    view = glm::lookAt(m_position, m_position + m_front, m_up);
    projection = glm::perspective(glm::radians(45.0f / m_zoom), static_cast<float>(width) / height, Perspective::Near, Perspective::Far);
    for (ShaderProgram& shaderProgram : shaderPrograms)
    {
        shaderProgram.use();
        shaderProgram.set("View", view);
        shaderProgram.set("Projection", projection);
    }
}

} // namespace kc
