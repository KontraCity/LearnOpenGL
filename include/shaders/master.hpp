#pragma once

// STL modules
#include <string>
#include <vector>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>

namespace kc {

namespace Shaders
{
    class Master
    {
    public:
        struct Color
        {
            uint8_t red = 255;
            uint8_t green = 255;
            uint8_t blue = 255;
            uint8_t opacity = 255;
        };

    private:
        /// @brief Convert shader type to name
        /// @param type Shader type
        /// @return Converted shader name
        static const char* ShaderTypeToName(int type);

        /// @brief Apply color to shader source
        /// @param source Shader source
        /// @param color The color to apply
        /// @return Shader source with applied color
        static std::string ApplyShaderColor(const char* source, const Color& color);

        /// @brief Compile shader from source
        /// @param source Shader source
        /// @param type Shader type
        /// @return Compiled shader
        static unsigned int CompileShader(const char* source, int type);

        /// @brief Link shader program
        /// @param shaders Shaders to link in the program
        /// @return Linked shader program
        static unsigned int LinkShaderProgram(const std::vector<unsigned int>& shaders);

    private:
        unsigned int m_vertexShader;
        unsigned int m_fragmentShader;
        unsigned int m_shaderProgram;

    public:
        /// @brief Initialize shaders master
        Master();

        ~Master();

        /// @brief Compile shaders and link shader program
        /// @param color Fragment shader color
        /// @throw std::runtime_error if compile/link error occurs
        void compile(const Color& color = {});

        /// @brief Free allocated resources
        /// @param freeProgram Whether to free shader program or not
        void free(bool freeProgram = true);

        /// @brief Tell OpenGL to use shader program
        inline void use() const
        {
            glUseProgram(m_shaderProgram);
        }
    };
}

} // namespace kc
