#pragma once

#include "../GLCall.h"
namespace Shengine {
    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void Create(uint32_t* data, uint32_t count);

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_RendererID;
    };
}