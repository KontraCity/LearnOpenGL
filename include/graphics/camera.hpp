#pragma once

// STL modules
#include <cmath>

// Graphics libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Custom modules
#include "common/utility.hpp"
#include "graphics/shader_program.hpp"

namespace kc {

namespace Graphics
{
    namespace CameraConst
    {
        namespace Speed
        {
            constexpr float Normal = 2.5f;
            constexpr float Fast = 6.0f;
            constexpr float Slow = 1.0f;
        }

        namespace Sensivity
        {
            constexpr float Move = 0.1f;
            constexpr float Scroll = 0.1f;
        }

        namespace Pitch
        {
            constexpr float Max = 89.9f;
            constexpr float Min = -Max;
        }

        namespace Zoom
        {
            constexpr float Max = 20.0f;
            constexpr float Min = 0.3f;
        }
        
        namespace Perspective
        {
            constexpr float Far = 100.0f;
            constexpr float Near = 0.1f;
        }
    }

    class Camera
    {
    public:
        enum class Key
        {
            ZoomReset,
            Up,
            Down,
            Forward,
            Backward,
            Left,
            Right,
        };

        enum class MovementMode
        {
            Normal,
            Fast,
            Slow,
        };

    private:
        /// @brief Convert movement mode to speed
        /// @param mode The mode to convert
        /// @return Converted movement speed
        static float MovementModeToSpeed(MovementMode mode);

    private:
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        float m_yaw;
        float m_pitch;
        float m_zoom;

    public:
        Camera();

        /// @brief Tell camera that keyboard key was pressed
        /// @param key The key that was pressed
        /// @param mode Camera movement mode
        /// @param deltaTime Frame delta time
        void keyPressed(Key key, MovementMode movementMode, float deltaTime);

        /// @brief Tell camera that mouse has moved
        /// @param xOffset Move x offset
        /// @param yOffset Move y offset
        void mouseMoved(int xOffset, int yOffset);

        /// @brief Tell camera that mouse has scrolled
        /// @param offset Scroll offset
        void mouseScrolled(int offset);

        /// @brief Apply camera calculations to shader program
        /// @param shaderProgram The shader program to apply to
        /// @param width Window width
        /// @param height Window height
        void capture(ShaderProgram& shaderProgram, unsigned int width, unsigned int height);
    };
}

} // namespace kc
