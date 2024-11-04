#pragma once

// Custom modules
#include "graphics/types/color.hpp"
#include "graphics/types/light_attenuation.hpp"
#include "graphics/types/light_properties.hpp"

namespace kc {

namespace Graphics
{
    namespace Lighting
    {
        class Light
        {
        protected:
            Color m_color;
            LightAttenuation m_attenuation;
            LightProperties m_properties;

        public:
            /// @brief Create light
            /// @param color Light color
            /// @param attenuation Light attenuation
            /// @param properties Light properties
            Light(Color color = {}, const LightAttenuation& attenuation = {}, const LightProperties& properties = {})
                : m_color(color)
                , m_attenuation(attenuation)
                , m_properties(properties)
            {}

            /// @brief Get light color
            /// @return Light color
            inline Color color() const
            {
                return m_color;
            }

            /// @brief Get light color
            /// @return Light color
            inline Color& color()
            {
                return m_color;
            }

            /// @brief Get light attenuatuin
            /// @return Light attenuation
            inline const LightAttenuation& attenuation() const
            {
                return m_attenuation;
            }

            /// @brief Get light attenuatuin
            /// @return Light attenuation
            inline LightAttenuation& attenuation()
            {
                return m_attenuation;
            }

            /// @brief Get light properties
            /// @return Light properties
            inline const LightProperties& properties() const
            {
                return m_properties;
            }

            /// @brief Get light properties
            /// @return Light properties
            inline LightProperties& properties()
            {
                return m_properties;
            }
        };
    }
}

} // namespace kc
