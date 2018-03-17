#pragma once

#include "ABehaviour.h"
#include "Mesh.h"

namespace Gyvr
{
	namespace Object
	{
		/*
		* 3D Model of an object (The gameObject always looks for this component to draw himself)
		*/
		class MeshRenderer : public ABehaviour
		{
		public:
			MeshRenderer();
			~MeshRenderer() = default;

			void SetMesh(Gyvr::Resource::Mesh* p_mesh);

			void Draw();

		private:
			Resource::Mesh* m_mesh;
		};
	}
}
