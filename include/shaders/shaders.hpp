#pragma once

namespace kc {

namespace Shaders
{
    namespace Sources
    {
        // Vertex shader source code
        // To be compiled as is
        constexpr const char* Vertex = { R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;

            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )" };

        // Fragment shader source code
        // Colors must be applied with fmt::format before compiling!
        constexpr const char* Fragment = { R"(
            #version 330 core
            out vec4 FragColor;

            void main()
            {{
                FragColor = vec4({:.3f}f, {:.3f}f, {:.3f}f, {:.3f}f);
            }}
        )" };
    }
}

} // namespace kc
