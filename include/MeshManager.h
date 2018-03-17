#pragma once

#include "AResourceManager.h"
#include "Mesh.h"

namespace Gyvr
{
	namespace Resource
	{
		/*
		 * Resource Manager that can handle textures
		 */
		class MeshManager : public AResourceManager<MeshManager, Mesh>
		{
		public:
			MeshManager() : AResourceManager("../config/resources/meshes.cfg") {}

			Mesh* Load(const std::string& l_path) override
			{
				Mesh* mesh = new Mesh();
				if (!mesh->LoadFromFile(l_path))
				{
					delete mesh;
					mesh = nullptr;
					Gyvr::Core::Debug::Log::Process("Failed to load mesh: " + l_path, Gyvr::Core::Debug::Log::LogLevel::LOG_ERROR);
				}

				mesh->InitMesh();

				return mesh;
			}
		};
	}
}