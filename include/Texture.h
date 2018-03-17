#pragma once

#include <string>

#include <stb_image.h>

namespace Gyvr
{
	namespace Resource
	{
		/*
		 * Texture is a class that encapsulate stb_image texture
		 */
		class Texture
		{
		public:
			Texture();
			~Texture();

			bool LoadFromFile(const std::string& p_path);

		private:
			int m_width;
			int m_height;
			int m_channelsInFile;
			unsigned char* m_textureBuffer;
		};
	}
}
