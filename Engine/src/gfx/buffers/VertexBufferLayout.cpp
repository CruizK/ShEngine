#include "VertexBufferLayout.h"

namespace Shengine {
    VertexBufferLayout::VertexBufferLayout()
        : m_Stride(0)
    {

    }

    VertexBufferLayout::~VertexBufferLayout()
    {

    }

    void VertexBufferLayout::PushFloat(uint32_t count)
    {
        Push(GL_FLOAT, count, GL_FALSE);
    }

    void VertexBufferLayout::PushUInt(uint32_t count)
    {
        Push(GL_UNSIGNED_INT, count, GL_FALSE);
    }

    void VertexBufferLayout::PushUChar(uint32_t count)
    {
        Push(GL_UNSIGNED_BYTE, count, GL_TRUE);
    }

    void VertexBufferLayout::Push(uint32_t type, uint32_t count, unsigned char normalized)
    {
        m_Elements.push_back({
            type,
            count,
            normalized,
            count * VertexBufferElement::GetSizeOfType(type)
            });

        m_Stride += m_Elements.back().size;
    }
}