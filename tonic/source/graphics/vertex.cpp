#include "tonic/graphics/vertex.h"
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

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    Push(GL_UNSIGNED_INT, count, GL_FALSE);
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    Push(GL_FLOAT, count, GL_FALSE);
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    Push(GL_UNSIGNED_BYTE, count, GL_TRUE);
}

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_VBO);
}

void VertexBuffer::Bind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ElementBuffer::ElementBuffer(const unsigned int *data, unsigned int count)
{
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &m_EBO);
}

void ElementBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
}

void ElementBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_VAO);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_VAO);
}

void VertexArray::SubmitBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const
{
    glBindVertexArray(m_VAO);
    vb.Bind();

    const auto &attributes = layout.GetAttributes();

    unsigned int offset = 0;
    for (unsigned int i = 0; i < attributes.size(); ++i)
    {
        auto &attrib = attributes[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attrib.count, attrib.type, attrib.normalized, layout.GetStride(), (void *)(intptr_t)(offset));
        offset += attrib.count * VertexBufferAttribute::GetSizeOfType(attrib.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_VAO);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
}