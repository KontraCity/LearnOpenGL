#include "graphics/mesh/mesh.hpp"

namespace kc {

Graphics::Mesh::Mesh::Mesh(int indicesCount)
    : m_indicesCount(indicesCount)
    , m_vertexArrayObject(0)
    , m_vertexBufferObject(0)
    , m_elementBufferObject(0)
{}

Graphics::Mesh::Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_elementBufferObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Graphics::Mesh::Mesh::draw() const
{
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);
}

} // namespace kc
