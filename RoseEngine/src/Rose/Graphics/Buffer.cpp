#include "Rose/Graphics/Buffer.hpp"

#include <glad/glad.h>

namespace Rose {

VertexBuffer::VertexBuffer() {}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_ID);
}
void VertexBuffer::generate(BufferType type)
{
    glGenBuffers(1, &m_ID);
    m_Type = type;
}

void VertexBuffer::addData(const GLfloat *data, size_t size){
    bind();
    if (m_Type == BufferType::Static) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }
    else if (m_Type == BufferType::Dynamic) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }
}

void VertexBuffer::updateData(const GLfloat *data, size_t size) {
    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer() {}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::generate() {
    glGenBuffers(1, &m_ID);
}

void IndexBuffer::addIndices(const GLuint *data, size_t size) {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray() {}

void VertexArray::generate() {
    glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::bind() const {
    glBindVertexArray(m_ID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) {
    bind();
    
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);

}

void VertexArray::addAttribute(const VertexAttribute &attribute) {
    bind();

    glVertexAttribPointer(attribute.index, 
                          attribute.size, 
                          attribute.type, 
                          attribute.normalized, 
                          attribute.stride, 
                          (GLvoid*)attribute.offset);

    glEnableVertexAttribArray(attribute.index);
}

void VertexArray::addInstancedAttribute(const VertexAttribute &attribute) {
    bind();
    
    glVertexAttribPointer(attribute.index, 
                          attribute.size, 
                          attribute.type, 
                          attribute.normalized, 
                          attribute.stride, 
                          (GLvoid*)attribute.offset);
        
    glEnableVertexAttribArray(attribute.index);
    glVertexAttribDivisor(attribute.index, 1);
}



} // namespace Rose
