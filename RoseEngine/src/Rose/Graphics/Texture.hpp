#pragma once

#include "Rose/Core/Core.hpp"
#include "Rose/Graphics/Image.hpp"
#include "Rose/Graphics/TextureParam.hpp"

#include <glad/glad.h>

namespace Rose {
class ROSE_API Texture {
public:
    Texture() = default;
    ~Texture();

    void generate(const std::filesystem::path &imagePath, const TextureParameter &params = TextureParameter());

    void bind() const;

    inline Image getImage() const { return m_Image; }
    inline GLuint ID() const { return m_ID; }
private:
    GLuint m_ID;
    Image m_Image;
};

}
