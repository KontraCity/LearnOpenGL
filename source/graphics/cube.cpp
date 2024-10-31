#include "graphics/cube.hpp"

namespace kc {

namespace Data
{
    constexpr float Vertices[] = {
        // Front
        // Coordinates         Normale coordinates    Texture coordinates
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f,

        // Right
        // Coordinates         Normale coordinates    Texture coordinates
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

        // Back
        // Coordinates         Normale coordinates    Texture coordinates
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,

        // Left
        // Coordinates         Normale coordinates    Texture coordinates
        -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

        // Top
        // Coordinates         Normale coordinates    Texture coordinates
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,

        // Bottom
        // Coordinates         Normale coordinates    Texture coordinates
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
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

Graphics::Cube::Cube()
    : Cube({}, {}, {})
{}

Graphics::Cube::Cube(const Transform& transform, Color color, const Material& material)
    : m_vertexArrayObject(0)
    , m_vertexBufferObject(0)
    , m_elementBufferObject(0)
    , m_transform(transform)
    , m_color(color)
    , m_material(material)
{
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Data::Vertices), Data::Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Data::Indices), Data::Indices, GL_STATIC_DRAW);
}

Graphics::Cube::~Cube()
{
    glDeleteBuffers(1, &m_elementBufferObject);
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Graphics::Cube::draw(ShaderProgram& shaderProgram) const
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

    // Set color and material
    shaderProgram.set("ObjectColor", m_color);
    shaderProgram.set("Material", m_material);

    // Draw
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, sizeof(Data::Indices), GL_UNSIGNED_INT, 0);
}

} // namespace kc
