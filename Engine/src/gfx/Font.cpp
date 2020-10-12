#include "Font.h"

namespace Shengine {

	Font::Font() 
		: m_Texture(nullptr), m_TextureAtlas(nullptr), m_TextureFont(nullptr)
	{

	}

	Font::~Font() {
		if (m_TextureFont != nullptr)
			ftgl::texture_font_delete(m_TextureFont);
		if (m_TextureAtlas != nullptr)
			ftgl::texture_atlas_delete(m_TextureAtlas);
	}

	Ref<Font> Font::Create(const std::string& path)
	{
		Ref<Font> f = CreateRef<Font>();
		f->LoadFromFile(path);
		return f;
	}

	void Font::LoadFromFile(const std::string& path)
	{
		if (m_TextureAtlas == nullptr)
			m_TextureAtlas = ftgl::texture_atlas_new(1024, 1024, 1);

		m_TextureFont = ftgl::texture_font_new_from_file(m_TextureAtlas, 50, path.c_str());
		m_TextureFont->padding = 1;
		if (m_TextureFont)
		{
			char* text = u8"ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstvuwxyz !? 0123456789";
			ftgl::texture_font_load_glyphs(m_TextureFont, text);

			GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));

			m_Texture = Texture2D::Create(m_TextureAtlas->data, m_TextureAtlas->width, m_TextureAtlas->height, 1);
		}
		else
		{
			CORE_ERROR("Failed to load font at path: {0}", path);
			return;
		}
	}

	ftgl::texture_glyph_t* Font::GetGlyph(const char* codepoint) const
	{
		if (!m_TextureFont) return nullptr;
		return ftgl::texture_font_find_glyph(m_TextureFont, codepoint);
	}
}