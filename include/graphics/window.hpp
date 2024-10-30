#pragma once

// STL modules
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Custom common modules
#include "common/stopwatch.hpp"
#include "common/utility.hpp"

// Custom graphics modules
#include "graphics/camera.hpp"
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

namespace kc {

namespace Graphics
{
    class Window
    {
    private:
        /// @brief GLFW framebuffer resize event callback
        /// @param window The window that received the event
        /// @param width New width
        /// @param height New height
        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

        /// @brief GLFW mouse cursor position event callback
        /// @param window The window that received the event
        /// @param x New cursor X coordinage
        /// @param y New cursor Y coordinate
        static void CursorPositionCallback(GLFWwindow* window, double x, double y);

        /// @brief GLFW mouse scroll event callback
        /// @param window The window that received the event
        /// @param xOffset X coordinage scroll offset
        /// @param yOffset Y coordinate scroll offset
        static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    private:
        /* Window specific */
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        Camera m_camera;

        /* Resources */
        ShaderProgram m_shaderProgram;
        Texture m_containerTexture;
        Texture m_awesomeFaceTexture;

        /* Variables */
        float m_deltaTime;
        float m_lastFrameTime;
        float m_textureMix;

    private:
        /// @brief Process keyboard input for current frame
        void processInput();

    public:
        /// @brief Create window and prepare for rendering
        /// @param width Window width
        /// @param height Window height
        /// @param resourcesDirectoryPath Path to resources directory
        /// @throw std::runtime_error if internal error occurs
        Window(unsigned int width, unsigned int height, const std::string& resourcesDirectoryPath);

        ~Window();

        /// @brief Run loop
        void run();
    };
}

} // namespace kc
