#include "Rose/Graphics/Texture.hpp"

#include <glad/glad.h>

namespace Rose {

Texture::~Texture() {
    glDeleteTextures(1, &m_ID);
}

void Texture::generate(const std::filesystem::path &imagePath, const TextureParameter &params) {
    glGenTextures(1, &m_ID);
    bind();
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureParameter::toGLWrap(params.WrapS));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureParameter::toGLWrap(params.WrapT));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureParameter::toGLFilter(params.MinifyFilter));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureParameter::toGLFilter(params.MagnifyFilter));

    m_Image.generate(imagePath);
    GLenum format = m_Image.getChannels() == 4 ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Image.getWidth(), m_Image.getHeight(), 0, format, GL_UNSIGNED_BYTE, m_Image.data());
    glGenerateMipmap(GL_TEXTURE_2D);

}

void Texture::generateFromBitmap(unsigned char *buffer, int32_t height, int32_t width) {
    glGenTextures(1, &m_ID);
    bind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        width,
        height,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        buffer
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);     
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

}
