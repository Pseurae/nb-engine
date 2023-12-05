#pragma once

#include <vector>

namespace tonic::graphics
{
struct VertexBufferAttribute
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type);
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() : m_Stride(0) { }
    ~VertexBufferLayout() = default;

    template<typename T>
    void Push(unsigned int count) { }

    template<>
    void Push<unsigned int>(unsigned int count);

    template<>
    void Push<float>(unsigned int count);

    template<>
    void Push<unsigned char>(unsigned int count);

    const auto &GetAttributes() const { return m_Attributes; }
    unsigned int GetStride() const { return m_Stride; }

private:
    void Push(unsigned int type, unsigned int count, unsigned char normalized);

    std::vector<VertexBufferAttribute> m_Attributes;
    unsigned int m_Stride;
};

class VertexBuffer
{
public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_VBO;
};

class ElementBuffer
{
public:
    ElementBuffer(const unsigned int *data, unsigned int count);
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_EBO;
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void SubmitBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) const;
    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_VAO;
};
}