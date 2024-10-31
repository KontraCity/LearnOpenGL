#pragma once

// Graphics libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Custom modules
#include "graphics/shader_program.hpp"

namespace kc {

namespace Graphics
{
    class Transform
    {
    protected:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;

    public:
        /// @brief Initialize transform
        Transform();

        /// @brief Initialize transform
        /// @param position Transform position
        /// @param rotation Transform rotation
        /// @param scale Transform scale
        Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

        /// @brief Apply transformations to shader program
        /// @param shaderProgram The shader program to apply to
        void transform(ShaderProgram& shaderProgram) const;

        /// @brief Get transform position
        /// @return Transform position
        inline const glm::vec3& position() const
        {
            return m_position;
        }

        /// @brief Get transform position
        /// @return Transform position
        inline glm::vec3& position()
        {
            return m_position;
        }

        /// @brief Get transform rotation
        /// @return Transform rotation
        inline const glm::vec3& rotation() const
        {
            return m_rotation;
        }

        /// @brief Get transform rotation
        /// @return Transform rotation
        inline glm::vec3& rotation()
        {
            return m_rotation;
        }

        /// @brief Get transform scale
        /// @return Transform scale
        inline const glm::vec3& scale() const
        {
            return m_scale;
        }

        /// @brief Get transform scale
        /// @return Transform scale
        inline glm::vec3& scale()
        {
            return m_scale;
        }
    };
}

} // namespace kc
