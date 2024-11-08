#pragma once

// STL modules
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

// Library ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Custom modules
#include "graphics/types/transform.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader_program.hpp"

namespace kc {

namespace Graphics
{
    class Model
    {
    private:
        /* Model specific */
        std::string m_directory;
        std::vector<Mesh> m_meshes;
        std::unordered_map<std::string, Texture::Pointer> m_textures;

        /* Variables */
        Transform m_transform;

    private:
        /// @brief Process model node
        /// @param scene Model scene
        /// @param node The node to process
        void processNode(const aiScene* scene, aiNode* node);

        /// @brief Create model mesh
        /// @param scene Model scene
        /// @param mesh The mesh to create
        void createMesh(const aiScene* scene, aiMesh* mesh);

        /// @brief Load mesh textures
        /// @param textures Mesh textures
        /// @param material Mesh material
        /// @param type Textures type
        void loadTextures(std::vector<Texture::Pointer>& textures, aiMaterial* material, aiTextureType type);

    public:
        Model() = default;

        Model(Model&& other) = delete;

        Model(const Model& other) = delete;

        /// @brief Load model
        /// @param modelFilePath Path to model file
        void load(const std::string& modelFilePath);

        /// @brief Draw model to the screen
        /// @param shaderProgram Shader program to draw with
        void draw(ShaderProgram& shaderProgram) const;

        /// @brief Get model transform
        /// @return Model transform
        inline const Transform& transform() const
        {
            return m_transform;
        }

        /// @brief Get model transform
        /// @return Model transform
        inline Transform& transform()
        {
            return m_transform;
        }
    };
}

} // namespace kc
