#pragma once

// STL modules
#include <stdexcept>

// Library {fmt}
#include <fmt/format.h>

// External modules
#include "external/stb_image.h"

namespace kc {

class Image
{
private:
    uint8_t* m_data;
    int m_width;
    int m_height;
    int m_channels;

public:
    /// @brief Open image file
    /// @param imageFilePath Image file path
    /// @param verticalFlip Whether to flip image vertically on load or not
    /// @throw std::runtime_error if image couldn't be opened
    Image(const std::string& imageFilePath, bool verticalFlip = false);

    ~Image();

    /// @brief Get image data
    /// @return Image data
    inline const uint8_t* data() const
    {
        return m_data;
    }

    /// @brief Get image width
    /// @return Image width
    inline int width() const
    {
        return m_width;
    }

    /// @brief Get image height
    /// @return Image width
    inline int height() const
    {
        return m_height;
    }

    /// @brief Get number of image channels
    /// @return Number of image channels
    inline int channels() const
    {
        return m_channels;
    }
};

} // namespace kc
