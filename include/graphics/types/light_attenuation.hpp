#pragma once

namespace kc {

namespace Graphics
{
    struct LightAttenuation
    {
        float constant = 0.2f;
        float linear = 0.09f;
        float quadratic = 0.032f;
    };
}

} // namespace kc
