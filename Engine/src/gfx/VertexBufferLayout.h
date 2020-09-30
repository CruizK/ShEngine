#pragma once

#include "GLCall.h"

struct VertexBufferElement
{
    uint32_t type;
    uint32_t count;
    unsigned char normalized;
    uint32_t size;

    static uint32_t GetSizeOfType(uint32_t type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        default:
            CORE_ERROR("Vertex Buffer Element of type does not exist");
        }
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    void PushFloat(uint32_t count);
    void PushUInt(uint32_t count);
    void PushUChar(uint32_t count);

    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }
    inline uint32_t GetStride() const { return m_Stride; }

private:
    void Push(uint32_t type, uint32_t count, unsigned char normalized);

    std::vector<VertexBufferElement> m_Elements;
    uint32_t m_Stride;
};