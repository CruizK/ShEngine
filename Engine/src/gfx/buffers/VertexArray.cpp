#include "VertexArray.h"


namespace Shengine {
    VertexArray::VertexArray()
        : m_RendererId(0), m_AttribIndex(0), m_AttribOffset(0)
    {
        GLCall(glGenVertexArrays(1, &m_RendererId));
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererId);
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
    {
        Bind();
        vb.Bind();

        const auto& elements = layout.GetElements();
        uint32_t offset = 0;
        for (uint32_t i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(i,
                element.count,
                element.type,
                element.normalized,
                layout.GetStride(),
                (void*)offset)
                );
            offset += element.size;
        }
    }

    void VertexArray::Bind()
    {
        GLCall(glBindVertexArray(m_RendererId));
    }

    void VertexArray::Unbind()
    {
        GLCall(glBindVertexArray(0));
    }
}