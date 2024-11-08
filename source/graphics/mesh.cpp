#include "graphics/mesh.hpp"

namespace kc {

Graphics::Mesh::Objects Graphics::Mesh::CreateMesh(const std::vector<Vertex>& vertices, const std::vector<Indice>& indices)
{
    Objects objects;
    glGenVertexArrays(1, &objects.vertexArray);
    glBindVertexArray(objects.vertexArray);

    glGenBuffers(1, &objects.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, objects.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &objects.elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indice) * indices.size(), indices.data(), GL_STATIC_DRAW);
    return objects;
}

void Graphics::Mesh::free()
{
    if (m_objects.elementBuffer)
    {
        glDeleteBuffers(1, &m_objects.elementBuffer);
        m_objects.elementBuffer = 0;
    }

    if (m_objects.vertexBuffer)
    {
        glDeleteBuffers(1, &m_objects.vertexBuffer);
        m_objects.vertexBuffer = 0;
    }

    if (m_objects.vertexArray)
    {
        glDeleteVertexArrays(1, &m_objects.vertexArray);
        m_objects.vertexArray = 0;
    }
}

Graphics::Mesh::Mesh()
    : m_objects({ 0, 0, 0 })
{}

Graphics::Mesh::Mesh(Mesh&& other) noexcept
    : m_objects(other.m_objects)
    , m_vertices(other.m_vertices)
    , m_indices(other.m_indices)
    , m_textures(other.m_textures)
{
    other.m_objects = { 0, 0, 0 };
    other.m_vertices.clear();
    other.m_indices.clear();
    other.m_textures.clear();
}

Graphics::Mesh::~Mesh()
{
    free();
}

void Graphics::Mesh::create()
{
    free(); // avoid memory leaks if load() was called already
    m_objects = CreateMesh(m_vertices, m_indices);
}

void Graphics::Mesh::draw(ShaderProgram& shaderProgram) const
{
    for (size_t index = 0, size = m_textures.size(); index < size; ++index)
    {
        std::string uniformName;
        switch (m_textures[index]->type())
        {
            case Texture::Type::Diffuse:
                uniformName = "Material.diffuse";
                break;
            case Texture::Type::Specular:
                uniformName = "Material.specular";
                break;
            default:
                // Unknown texture! Can't set anything...
                continue;
        }

        glActiveTexture(GL_TEXTURE0 + index);
        shaderProgram.set(uniformName, static_cast<int>(index));
        glBindTexture(GL_TEXTURE_2D, m_textures[index]->id());
    }

    glBindVertexArray(m_objects.vertexArray);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} // namespace kc
