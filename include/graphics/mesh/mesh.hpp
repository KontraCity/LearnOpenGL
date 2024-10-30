#pragma once

// Graphics libraries
#include <GL/glew.h>

namespace kc {

namespace Graphics
{
    namespace Mesh
    {
        class Mesh
        {
        protected:
            const int m_indicesCount;
            unsigned int m_vertexArrayObject;
            unsigned int m_vertexBufferObject;
            unsigned int m_elementBufferObject;

        public:
            /// @brief Initialize mesh
            /// @param indicesCount Count of indices in mesh
            Mesh(int indicesCount);

            ~Mesh();

            /// @brief Create mesh
            virtual void create() = 0;

            /// @brief Draw mesh to the screen
            void draw() const;
        };
    }
}

} // namespace kc
