#pragma once

#include "Rose/Core/Core.hpp"

namespace Rose {

class ROSE_API Image {
public:
    Image() = default;
    Image(const std::filesystem::path &path);
    ~Image();

    void generate(const std::filesystem::path &path);
    
    inline unsigned char *data() { return m_Data; }
    inline uint32_t getWidth() { return m_Width; }
    inline uint32_t getHeight() { return m_Height; }
    inline uint32_t getChannels() { return m_Channels; }

    inline void setExternalData(unsigned char* data, int32_t width, int32_t height, int32_t channels) {
        m_Data = data;
        m_Width = width;
        m_Height = height;
        m_Channels = channels;
        m_OwnsData = false;
    }
private:
    unsigned char *m_Data;
    int32_t m_Width;
    int32_t m_Height;
    int32_t m_Channels;
    bool m_OwnsData;
};

}
