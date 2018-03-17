#pragma once

#include "AResourceManager.h"
#include "Texture.h"

namespace Gyvr
{
	namespace Resource
	{
		/*
		 * Resource Manager that can handle textures
		 */
		class TextureManager : public AResourceManager<TextureManager, Texture>
		{
		public:
			TextureManager() : AResourceManager("../config/resources/textures.cfg") {}

			Texture* Load(const std::string& l_path) override
			{
				Texture* texture = new Texture();
				if (!texture->LoadFromFile(l_path))
				{
					delete texture;
					texture = nullptr;
					Gyvr::Core::Debug::Log::Process("Failed to load texture: " + l_path, Gyvr::Core::Debug::Log::LogLevel::LOG_ERROR);
				}

				return texture;
			}
		};
	}
}