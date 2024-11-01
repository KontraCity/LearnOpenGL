#pragma once

// STL modules
#include <fstream>
#include <sstream>
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// Graphics libraries
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Custom modules
#include "graphics/types/color.hpp"
#include "graphics/types/light_properties.hpp"
#include "graphics/types/material.hpp"
#include "graphics/texture.hpp"

namespace kc {

namespace Graphics
{
    class ShaderProgram
    {
    private:
        /// @brief Read file
        /// @param filePath Path to the file
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
        /// @param vertexShaderFilePath Path to vertex shader source file
        /// @param fragmentShaderFilePath Path to fragment shader source file
        /// @throw std::runtime_error if read/compile/link error occurs
        void make(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

        /// @brief Tell OpenGL to use this shader program
        void use() const;

        /// @brief Set uniform boolean
        /// @param name Boolean name
        /// @param boolean The boolean to set
        void set(const std::string& name, bool boolean);

        /// @brief Set uniform integer
        /// @param name Integer name
        /// @param integer The integer to set
        void set(const std::string& name, int integer);

        /// @brief Set uniform real
        /// @param name Real name
        /// @param real The real to set
        void set(const std::string& name, float real);

        /// @brief Set uniform vector
        /// @param name Vector name
        /// @param vector The vector to set
        void set(const std::string& name, const glm::vec3& vector);

        /// @brief Set uniform matrix
        /// @param name Matrix name
        /// @param matrix The matrix to set
        void set(const std::string& name, const glm::mat4& matrix);

        /// @brief Set uniform color struct
        /// @param name Color struct name
        /// @param color The color struct to set
        void set(const std::string& name, Color color);

        /// @brief Set uniform light properties struct
        /// @param name Light properties struct name
        /// @param lightProperties The light properties struct to set
        void set(const std::string& name, const LightProperties& lightProperties);

        /// @brief Set uniform material struct
        /// @param name Material struct name
        /// @param material The material struct to set
        void set(const std::string& name, const Material& material);

        /// @brief Set uniform texture
        /// @param name Texture name
        /// @param texture The texture to set
        /// @param id Texture ID
        void set(const std::string& name, const Texture& texture, int id);
    };
}

} // namespace kc
