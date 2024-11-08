#pragma once

// STL modules
#include <vector>
#include <functional>

// Graphics libraries
#include <GL/glew.h>
#include <glm/glm.hpp>

// Custom modules
#include "graphics/shader_program.hpp"
#include "graphics/texture.hpp"

namespace kc {

namespace Graphics
{
    class Mesh
    {
    public:
        struct Vertex
        {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 texCoords;
        };

        using Indice = unsigned int;

    private:
        struct Objects
        {
            unsigned int vertexArray;
            unsigned int vertexBuffer;
            unsigned int elementBuffer;
        };

    private:
        /// @brief Create mesh
        /// @param vertices Mesh vertices
        /// @param indices Mesh indices
        /// @return Created objects
        static Objects CreateMesh(const std::vector<Vertex>& vertices, const std::vector<Indice>& indices);

    private:
        Objects m_objects;
        std::vector<Vertex> m_vertices;
        std::vector<Indice> m_indices;
        std::vector<Texture::Pointer> m_textures;

    private:
        /// @brief Free allocated resources
        void free();

    public:
        Mesh();

        Mesh(Mesh&& other) noexcept;

        Mesh(const Mesh& other) = delete;

        ~Mesh();

        /// @brief Create mesh
        void create();

        /// @brief Draw mesh to the screen
        /// @param shaderProgram Shader program to draw with
        void draw(ShaderProgram& shaderProgram) const;

        /// @brief Get mesh vertices
        /// @return Mesh vertices
        inline std::vector<Vertex>& vertices()
        {
            return m_vertices;
        }

        /// @brief Get mesh indices
        /// @return Mesh indices
        inline std::vector<Indice>& indices()
        {
            return m_indices;
        }

        /// @brief Get mesh textures
        /// @return Mesh textures
        inline std::vector<Texture::Pointer>& textures()
        {
            return m_textures;
        }
    };
}

} // namespace kc
