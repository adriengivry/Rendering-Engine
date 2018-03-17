#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Vec3.h"

namespace Gyvr
{
	namespace Resource
	{
		struct Vertex
		{
			Math::Vec3 position;
			Math::Vec3 normal;
		};

		/*
		* A resource that can be given to a MeshRenderer in order to get displayed
		*/
		class Mesh
		{
		public:
			Mesh();
			~Mesh();

			bool LoadFromFile(const std::string& p_path);
			void InitMesh();

			GLuint& GetVBO();
			GLuint& GetVAO();
			GLuint& GetEBO();

			std::vector<Vertex>& GetVertices();
			std::vector<GLuint>& GetIndices();
		private:
			GLuint m_vbo;;
			GLuint m_vao;
			GLuint m_ebo;

			std::vector<Vertex> m_vertices;
			std::vector<GLuint> m_indices;
		};
	}
}