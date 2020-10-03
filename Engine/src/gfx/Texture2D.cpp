#include "Texture2D.h"
#include <stb_image.h>

Texture2D::Texture2D()
	: m_TextureID(0), m_Size(0, 0)
{
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture2D::LoadFromFile(const std::string& path)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, channels = 0;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	if (data)
	{
		LoadFromMemory(data, width, height, channels);
	}
	else
	{
		CORE_ERROR("Could not load texture: {0}", path);
	}

	stbi_image_free(data);
}

void Texture2D::LoadFromMemory(void* data, uint32_t width, uint32_t height, int channels)
{
	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	uint32_t internalFormat = 0;
	uint32_t dataFormat = 0;

	CORE_ASSERT(channels == 1 || channels == 3 || channels == 4, "Specified unsupported amount of channels");

	if (channels == 3)
	{
		internalFormat = GL_RGB;
		dataFormat = GL_RGB;
	}
	else if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}

	CORE_TRACE("(LOADING TEXTURE) Width: {0} | Height: {1} | Channels: {2}", width, height, channels);

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	m_Size = Size(width, height);
}

void Texture2D::Bind(uint32_t slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
}

void Texture2D::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
