#pragma once

#include <ftgl/texture-font.h>
#include <ftgl/texture-atlas.h>
#include <string>
#include "../core/Base.h"
#include "Texture2D.h"

namespace Shengine {

	class Font
	{
	public:
		Font();
		~Font();

		static Ref<Font> Create(const std::string& path);
		
		ftgl::texture_glyph_t* GetGlyph(const char* codepoint) const;

		inline const Ref<Texture2D>& GetTexture() { return m_Texture; }


	private:

		void LoadFromFile(const std::string& path);

		Ref<Texture2D> m_Texture;
		ftgl::texture_font_t* m_TextureFont;
		ftgl::texture_atlas_t* m_TextureAtlas;
	};
}