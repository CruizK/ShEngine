#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind();
    void Unbind();

private:
    uint32_t m_RendererId;
    uint32_t m_AttribIndex, m_AttribOffset;
};