#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
    : m_RendererID(0)
{
}

VertexBuffer::VertexBuffer(void* data, uint32_t size)
    : m_RendererID(0)
{
    Create(data, size);
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Create(void* data, uint32_t size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

void VertexBuffer::UploadSubData(void* data, uint32_t size, uint32_t offset)
{
    Bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}