#pragma once

// STL modules
#include <string>
#include <stdexcept>

// Graphics libraries
#include <GL/glew.h>

// Custom modules
#include "common/image.hpp"

namespace kc {

namespace Graphics
{
    class Texture
    {
    private:
        /// @brief Load texture from image file
        /// @param imageFilePath Path to image file
        /// @param format Image format (GL_RGB, GL_RGBA, etc)
        /// @param verticalFlip Whether to flip texture vertically or not
        /// @throw std::runtime_error if texture couldn't be loaded
        static unsigned int LoadTexture(const std::string& imageFilePath, int format, bool verticalFlip);

    private:
        unsigned int m_texture;

    private:
        /// @brief Free allocated resources
        void free();

    public:
        Texture();

        ~Texture();

        /// @brief Load texture from image file
        /// @param imageFilePath Path to image file
        /// @param format Image format (GL_RGB, GL_RGBA, etc)
        /// @param verticalFlip Whether to flip texture vertically or not
        /// @throw std::runtime_error if texture couldn't be loaded
        void load(const std::string& imageFilePath, int format = GL_RGB, bool verticalFlip = false);

        /// @brief Bind this texture
        void bind() const;

        /// @brief Set texture filtering mode for direction
        /// @param direction Filtering direction (GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, etc)
        /// @param mode The filtering mode to set (GL_NEAREST, GL_LINEAR, etc)
        void setFiltering(int direction, int mode);

        /// @brief Set texture filtering mode for all directions
        /// @param mode The filtering mode to set (GL_NEAREST, GL_LINEAR, etc)
        void setFiltering(int mode);

        /// @brief Set texture wrapping mode for direction
        /// @param direction Wrapping direction (GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, etc)
        /// @param mode The wrapping mode to set (GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, etc)
        void setWrapping(int direction, int mode);

        /// @brief Set texture wrapping mode for all directions
        /// @param mode The wrapping mode to set (GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, etc)
        void setWrapping(int mode);
    };
}

} // namespace kc
