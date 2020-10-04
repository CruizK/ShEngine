#pragma once

#include "../GLCall.h"

namespace Shengine {
    class VertexBuffer
    {
    public:
        VertexBuffer();
        VertexBuffer(void* data, uint32_t size);
        ~VertexBuffer();

        void Create(void* data, uint32_t size);
        void UploadSubData(void* data, uint32_t size, uint32_t offset);

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_RendererID;
    };
}