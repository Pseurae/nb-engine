#include "tonic/graphics/vertex.h"
#include "tonic/graphics/helpers.h"
#include <GL/gl3w.h>

namespace tonic::graphics
{
unsigned int VertexBufferAttribute::GetSizeOfType(unsigned int type)
{
    switch (type)
    {
    case GL_UNSIGNED_BYTE:
    case GL_BYTE:
        return 1;
    case GL_SHORT:
        return 2;
    case GL_FLOAT:
    case GL_UNSIGNED_INT:
    case GL_INT:
        return 4;
    default:
        return 0;
    }
}

void VertexBufferLayout::Push(unsigned int type, unsigned int count, unsigned char normalized)
{
    m_Attributes.push_back({ type, count, normalized });
    m_Stride += VertexBufferAttribute::GetSizeOfType(type) * count;
}

NB_VERTEXBUFFER_TYPE_REGISTER(unsigned int)
{
    Push(GL_UNSIGNED_INT, count, GL_FALSE);
}

NB_VERTEXBUFFER_TYPE_REGISTER(float)
{
    Push(GL_FLOAT, count, GL_FALSE);
}

NB_VERTEXBUFFER_TYPE_REGISTER(unsigned char)
{
    Push(GL_UNSIGNED_BYTE, count, GL_TRUE);
}

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &m_VBO); TONIC_CHECK_GL_ERROR();

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); TONIC_CHECK_GL_ERROR();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); TONIC_CHECK_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, 0); TONIC_CHECK_GL_ERROR();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_VBO); TONIC_CHECK_GL_ERROR();
}

void VertexBuffer::Bind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO); TONIC_CHECK_GL_ERROR();
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0); TONIC_CHECK_GL_ERROR();
}

ElementBuffer::ElementBuffer(const unsigned int *data, unsigned int count)
{
    glGenBuffers(1, &m_EBO); TONIC_CHECK_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); TONIC_CHECK_GL_ERROR();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW); TONIC_CHECK_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); TONIC_CHECK_GL_ERROR();
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &m_EBO); TONIC_CHECK_GL_ERROR();
}

void ElementBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); TONIC_CHECK_GL_ERROR();
}

void ElementBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); TONIC_CHECK_GL_ERROR();
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_VAO); TONIC_CHECK_GL_ERROR();
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_VAO); TONIC_CHECK_GL_ERROR();
}

void VertexArray::SubmitBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const
{
    glBindVertexArray(m_VAO); TONIC_CHECK_GL_ERROR();
    vb.Bind();

    const auto &attributes = layout.GetAttributes();

    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); ++i)
    {
        auto &attrib = attributes[i];

        glEnableVertexAttribArray(i); TONIC_CHECK_GL_ERROR();
        glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, layout.GetStride(), (void *)(intptr_t)(offset)); TONIC_CHECK_GL_ERROR();
        offset += attrib.count * VertexBufferAttribute::GetSizeOfType(attrib.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_VAO); TONIC_CHECK_GL_ERROR();
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0); TONIC_CHECK_GL_ERROR();
}
}