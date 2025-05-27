#pragma once

#include "Rose/Core/Core.hpp"

#include <glad/glad.h>

namespace Rose {

enum class ROSE_API WrapMode {
    Repeat,
    MirroredRepeat,
    ClampToEdge,
    ClampToBorder
};

enum class ROSE_API FilterMode {
    Nearest,
    Linear,
    NearestMipmapNearest,
    LinearMipmapNearest,
    NearestMipmapLinear,
    LinearMipmapLinear
};


struct ROSE_API TextureParameter {
    WrapMode WrapS = WrapMode::Repeat;
    WrapMode WrapT = WrapMode::Repeat;
    FilterMode MinifyFilter = FilterMode::LinearMipmapLinear;
    FilterMode MagnifyFilter = FilterMode::Linear;

    TextureParameter() = default;
    TextureParameter(WrapMode ws, WrapMode wt, FilterMode minF, FilterMode magF);

    static GLenum toGLWrap(WrapMode mode);
    static GLenum toGLFilter(FilterMode mode);
};

}
