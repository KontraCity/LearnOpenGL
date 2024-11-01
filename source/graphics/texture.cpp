#include "graphics/texture.hpp"

namespace kc {

unsigned int Graphics::Texture::LoadTexture(const std::string& imageFilePath, int format, bool verticalFlip)
{
    Image image(imageFilePath, verticalFlip);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, format, image.width(), image.height(), 0, format, GL_UNSIGNED_BYTE, image.data());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

void Graphics::Texture::free()
{
    if (m_texture)
    {
        glDeleteTextures(1, &m_texture);
        m_texture = 0;
    }
}

Graphics::Texture::Texture()
    : m_texture(0)
{}

Graphics::Texture::~Texture()
{
    free();
}

void Graphics::Texture::load(const std::string& imageFilePath, int format, bool verticalFlip)
{
    free(); // avoid memory leaks if load() was called already
    m_texture = LoadTexture(imageFilePath, format, verticalFlip);
    setFiltering(GL_LINEAR);
}

void Graphics::Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Graphics::Texture::setFiltering(int direction, int mode)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, direction, mode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::Texture::setFiltering(int mode)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::Texture::setWrapping(int direction, int mode)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, direction, mode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Graphics::Texture::setWrapping(int mode)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace kc
