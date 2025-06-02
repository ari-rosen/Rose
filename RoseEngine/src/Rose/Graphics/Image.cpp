#include "Rose/Graphics/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Rose {

Image::Image(const std::filesystem::path &path) {
    generate(path);
}

Image::~Image() {
    if (m_Data && m_OwnsData) {
        stbi_image_free(m_Data);
        m_Data = nullptr;
    }
}

void Image::generate(const std::filesystem::path &path) {
    stbi_set_flip_vertically_on_load(true);
    m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0); 
    m_OwnsData = true;
    
    if (!m_Data) {
        std::cout << "[ROSE]: Failed to load image: " << path << "; " << stbi_failure_reason() << std::endl;
    }
}


}
