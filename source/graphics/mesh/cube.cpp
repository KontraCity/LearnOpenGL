#include "graphics/mesh/cube.hpp"

namespace kc {

namespace Data
{
    constexpr float Vertices[] = {
        // Front
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,

        // Right
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,

        // Back
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,

        // Left
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,

        // Top
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

         // Bottom
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
    };

    constexpr int Indices[] = {
        // Front
        0, 1, 2,
        1, 2, 3,

        // Right
        4, 5, 6,
        5, 6, 7,

        // Back
        8, 9, 10,
        9, 10, 11,

        // Left
        12, 13, 14,
        13, 14, 15,

        // Top
        16, 17, 18,
        17, 18, 19,

        // Bottom
        20, 21, 22,
        21, 22, 23,
    };
}

Graphics::Mesh::Cube::Cube()
    : Mesh(sizeof(Data::Indices))
{}

void Graphics::Mesh::Cube::create()
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Data::Vertices), Data::Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Data::Indices), Data::Indices, GL_STATIC_DRAW);
}

} // namespace kc
