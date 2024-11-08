#include "graphics/model.hpp"

namespace kc {

void Graphics::Model::processNode(const aiScene* scene, aiNode* node)
{
    m_meshes.reserve(m_meshes.size() + node->mNumMeshes);
    for (unsigned int index = 0; index < node->mNumMeshes; ++index)
        createMesh(scene, scene->mMeshes[node->mMeshes[index]]);

    for (unsigned int index = 0; index < node->mNumChildren; ++index)
        processNode(scene, node->mChildren[index]);
}

void Graphics::Model::createMesh(const aiScene* scene, aiMesh* mesh)
{
    Mesh& meshEntry = m_meshes.emplace_back();

    std::vector<Mesh::Vertex>& vertices = meshEntry.vertices();
    vertices.reserve(mesh->mNumVertices);
    for (unsigned int index = 0; index < mesh->mNumVertices; ++index)
    {
        Mesh::Vertex& vertex = vertices.emplace_back();
        vertex.position = { mesh->mVertices[index].x, mesh->mVertices[index].y, mesh->mVertices[index].z };
        vertex.normal = { mesh->mNormals[index].x, mesh->mNormals[index].y, mesh->mNormals[index].z };
        vertex.texCoords = mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y) : glm::vec2(0.0f);
    }

    std::vector<Mesh::Indice>& indices = meshEntry.indices();
    for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
    {
        indices.reserve(indices.size() + mesh->mNumFaces);
        for (unsigned int indiceIndex = 0; indiceIndex < mesh->mFaces[faceIndex].mNumIndices; ++indiceIndex)
            indices.push_back(mesh->mFaces[faceIndex].mIndices[indiceIndex]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture::Pointer>& textures = meshEntry.textures();
        loadTextures(textures, material, aiTextureType_DIFFUSE);
        loadTextures(textures, material, aiTextureType_SPECULAR);
    }

    meshEntry.create();
}

void Graphics::Model::loadTextures(std::vector<Texture::Pointer>& textures, aiMaterial* material, aiTextureType type)
{
    Texture::Type textureType = Texture::Type::None;
    switch (type)
    {
        case aiTextureType_DIFFUSE:
            textureType = Texture::Type::Diffuse;
            break;
        case aiTextureType_SPECULAR:
            textureType = Texture::Type::Specular;
            break;
        default:
            // Unknown texture! Can't load anything...
            return;
    }

    unsigned int textureCount = material->GetTextureCount(type);
    textures.reserve(textures.size() + textureCount);
    for (unsigned int index = 0; index < textureCount; ++index)
    {
        aiString filename;
        material->GetTexture(type, index, &filename);

        if (m_textures.find(filename.C_Str()) != m_textures.end())
        {
            textures.push_back(m_textures[filename.C_Str()]);
            continue;
        }

        auto texture = m_textures.try_emplace(filename.C_Str());
        texture.first->second = std::make_shared<Texture>(textureType, m_directory + '/' + filename.C_Str(), GL_RGB, true);
        textures.push_back(texture.first->second);
    }
}

void Graphics::Model::load(const std::string& modelFilePath)
{
    m_directory = modelFilePath.substr(0, modelFilePath.find_last_of("/"));
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        throw std::runtime_error(fmt::format("kc::Graphics::Model::load(): Couldn't load model \"{}\"", modelFilePath));
    processNode(scene, scene->mRootNode);
}

void Graphics::Model::draw(ShaderProgram& shaderProgram) const
{
    // Transform
    // TODO: Rotate model around a single axis rather than three
    glm::mat4 model(1.0f);
    model = glm::translate(model, m_transform.position);
    model = glm::rotate(model, glm::radians(m_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(m_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, m_transform.scale);
    shaderProgram.set("Model", model);

    // Draw
    shaderProgram.set("Material.shininess", 32.0f);
    for (const Mesh& mesh : m_meshes)
        mesh.draw(shaderProgram);
}

} // namespace kc
