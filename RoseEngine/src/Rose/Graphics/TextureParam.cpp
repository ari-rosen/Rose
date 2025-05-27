#include "Rose/Graphics/TextureParam.hpp"

#include <glad/glad.h>

namespace Rose {

TextureParameter::TextureParameter(WrapMode ws, WrapMode wt, FilterMode minF, FilterMode magF)
    : WrapS(ws), WrapT(wt), MinifyFilter(minF), MagnifyFilter(magF) {}

GLenum TextureParameter::toGLWrap(WrapMode mode) {
    switch (mode) {
        case WrapMode::Repeat: return GL_REPEAT;
        case WrapMode::MirroredRepeat: return GL_MIRRORED_REPEAT;
        case WrapMode::ClampToEdge: return GL_CLAMP_TO_EDGE;
        case WrapMode::ClampToBorder: return GL_CLAMP_TO_BORDER;
    }
    return GL_REPEAT;
}

GLenum TextureParameter::toGLFilter(FilterMode mode) {
    switch (mode) {
        case FilterMode::Nearest: return GL_NEAREST;
        case FilterMode::Linear: return GL_LINEAR;
        case FilterMode::NearestMipmapNearest: return GL_NEAREST_MIPMAP_NEAREST;
        case FilterMode::LinearMipmapNearest: return GL_LINEAR_MIPMAP_NEAREST;
        case FilterMode::NearestMipmapLinear: return GL_NEAREST_MIPMAP_LINEAR;
        case FilterMode::LinearMipmapLinear: return GL_LINEAR_MIPMAP_LINEAR;
    }
    return GL_LINEAR;
}

}
