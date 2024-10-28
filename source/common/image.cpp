#include "common/image.hpp"

namespace kc {

Image::Image::Image(const std::string& imageFilePath, bool verticalFlip)
    : m_data(nullptr)
    , m_width(0)
    , m_height(0)
    , m_channels(0)
{
    stbi_set_flip_vertically_on_load(verticalFlip);
    m_data = stbi_load(imageFilePath.c_str(), &m_width, &m_height, &m_channels, 0);
    if (!m_data)
        throw std::runtime_error(fmt::format("kc::Image::Image(): Couldn't open image file \"{}\"", imageFilePath));
}

Image::Image::~Image()
{
    stbi_image_free(m_data);
}

} // namespace kc
