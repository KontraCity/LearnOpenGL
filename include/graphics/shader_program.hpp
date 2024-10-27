#pragma once

// STL modules
#include <fstream>
#include <sstream>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>

namespace kc {

namespace Graphics
{
    class ShaderProgram
    {
    private:
        /// @brief Read file
        /// @param filePath File path
        /// @throw std::runtime_error if file couldn't be opened
        /// @return File contents
        static std::string ReadFile(const std::string& filePath);

        /// @brief Convert shader type to name
        /// @param type Shader type
        /// @return Converted shader name
        static const char* ShaderTypeToName(int type);

        /// @brief Compile shader from source
        /// @param source Shader source
        /// @param type Shader type
        /// @throw std::runtime_error if compile error occurs
        /// @return Compiled shader
        static unsigned int CompileShader(const char* source, int type);

        /// @brief Link shader program
        /// @param vertexShader Compiled vertex shader
        /// @param fragmentShader Compiled framgent shader
        /// @throw std::runtime_error if link error occurs
        /// @return Linked shader program
        static unsigned int LinkShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

    private:
        unsigned int m_vertexShader;
        unsigned int m_fragmentShader;
        unsigned int m_shaderProgram;

    private:
        /// @brief Free allocated resources
        /// @param freeProgram Whether to free shader program or not
        void free(bool freeProgram = true);

    public:
        ShaderProgram();

        ~ShaderProgram();

        /// @brief Read, compile shaders and link shader program
        /// @param vertexShaderFilePath Vertex shader source file path
        /// @param fragmentShaderFilePath Fragment shader source file path
        /// @throw std::runtime_error if read/compile/link error occurs
        void make(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

        /// @brief Tell OpenGL to use this shader program
        inline void use() const
        {
            glUseProgram(m_shaderProgram);
        }
    };
}

} // namespace kc
