/*
 * Macro required to get stb_image working (Needs to be defined before #include <stb_image.h>
 */
#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

Gyvr::Resource::Texture::Texture()
{
	m_textureBuffer = nullptr;
	m_width = 0;
	m_height = 0;
	m_channelsInFile = 0;
}

Gyvr::Resource::Texture::~Texture()
{
	stbi_image_free(m_textureBuffer);
}

bool Gyvr::Resource::Texture::LoadFromFile(const std::string& p_path)
{
	stbi_set_flip_vertically_on_load(true);
	m_textureBuffer = stbi_load(p_path.c_str(), &m_width, &m_height, &m_channelsInFile, 0);
	return m_textureBuffer != nullptr;
}
