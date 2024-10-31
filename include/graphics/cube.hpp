#pragma once

// Graphics libraries
#include <GL/glew.h>

// Custom libraries
#include "graphics/types/color.hpp"
#include "graphics/types/material.hpp"
#include "graphics/types/transform.hpp"
#include "graphics/shader_program.hpp"

namespace kc {

namespace Graphics
{
    class Cube
    {
    private:
        unsigned int m_vertexArrayObject;
        unsigned int m_vertexBufferObject;
        unsigned int m_elementBufferObject;

    protected:
        Transform m_transform;
        Color m_color;
        Material m_material;

    public:
        /// @brief Crate cube
        Cube();

        /// @brief Crate cube
        /// @param transform Cube transform
        /// @parma color Cube color
        /// @param material Cube material
        Cube(const Transform& transform, Color color, const Material& material);

        ~Cube();

        /// @brief Draw cube to the screen
        /// @param shaderProgram Shader program to draw with
        void draw(ShaderProgram& shaderProgram) const;

        /// @brief Get cube transform
        /// @return Cube transform
        inline const Transform& transform() const
        {
            return m_transform;
        }

        /// @brief Get cube transform
        /// @return Cube transform
        inline Transform& transform()
        {
            return m_transform;
        }

        /// @brief Get cube color
        /// @return Cube color
        inline Color color() const
        {
            return m_color;
        }

        /// @brief Get cube color
        /// @return Cube color
        inline Color& color()
        {
            return m_color;
        }

        /// @brief Get cube material
        /// @return Cube material
        inline const Material& material() const
        {
            return m_material;
        }

        /// @brief Get cube material
        /// @return Cube material
        inline Material& material()
        {
            return m_material;
        }
    };
}

} // namespace kc
