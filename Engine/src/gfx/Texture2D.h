#pragma once

#include "GLCall.h"
#include "../core/Size.h"
#include "../core/Base.h"

#include <string>

namespace Shengine {

	class Texture2D
	{
	public:
		Texture2D();
		~Texture2D();

		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(void* data, uint32_t width, uint32_t height, int channels);


		void LoadFromFile(const std::string& path);
		void LoadFromMemory(void* data, uint32_t width, uint32_t height, int channels);


		inline const Size& getSize() { return m_Size; }

		void Bind(uint32_t slot) const;
		void Unbind() const;

		bool operator==(const Texture2D& other) const
		{
			return m_TextureID == other.m_TextureID;
		}

	private:

		uint32_t m_TextureID;
		Size m_Size;
	};
}