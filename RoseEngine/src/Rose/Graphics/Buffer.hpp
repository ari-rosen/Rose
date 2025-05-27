#pragma once

#include "Rose/Core/Core.hpp"

#include <glad/glad.h>

namespace Rose {

enum class BufferType {
    Static,
    Dynamic
};

class ROSE_API VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();
    
    void generate(BufferType type);
    void addData(const GLfloat *data, size_t size);
    void updateData(const GLfloat *data, size_t size);
    
    void bind() const;
    void unbind() const;
private:
    GLuint m_ID;
    BufferType m_Type;
};

class ROSE_API IndexBuffer {
public:
    IndexBuffer();
    ~IndexBuffer();

    void generate();
    void addIndices(const GLuint *indices, size_t size);

    void bind() const;
    void unbind() const;
private:
    GLuint m_ID;
};

struct ROSE_API VertexAttribute {
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    size_t stride;
    size_t offset;
};

class ROSE_API VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void generate();
    
    void bind() const;
    void unbind() const;

    void addAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    void addAttribute(const VertexAttribute &attribute);
    void addInstancedAttribute(const VertexAttribute &atribute);
private:
    GLuint m_ID;
};

}
