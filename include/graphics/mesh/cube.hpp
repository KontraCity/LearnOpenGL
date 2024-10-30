#pragma once

// Custom modules
#include "graphics/mesh/mesh.hpp"

namespace kc {

namespace Graphics
{
    namespace Mesh
    {
        class Cube : public Mesh
        {
        public:
            Cube();

            /// @brief Create cube
            void create();
        };
    }
}

} // namespace kc
