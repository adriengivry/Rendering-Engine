#include "Mesh.h"

using namespace Gyvr::Resource;

Mesh::Mesh()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
}

Mesh::~Mesh() {}

bool Mesh::LoadFromFile(const std::string& p_path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(p_path, aiProcess_Triangulate | aiProcess_GenNormals);

	if (!scene)
		return false;

	aiMesh* mesh = scene->mMeshes[0];	

	for (uint64_t j = 0; j < mesh->mNumVertices; ++j)
	{
		Vertex tempVertex;

		tempVertex.position.x = mesh->mVertices[j].x;
		tempVertex.position.y = mesh->mVertices[j].y;
		tempVertex.position.z = mesh->mVertices[j].z;

		tempVertex.normal.x = mesh->mNormals[j].x;
		tempVertex.normal.y = mesh->mNormals[j].y;
		tempVertex.normal.z = mesh->mNormals[j].z;

		m_vertices.push_back(tempVertex);
	}

	for (uint64_t j = 0; j < mesh->mNumFaces; ++j)
	{
		aiFace face = mesh->mFaces[j];

		for (unsigned int k = 0; k < face.mNumIndices; ++k) 
			m_indices.push_back(face.mIndices[k]); 
	}
	
	return true;
}

void Gyvr::Resource::Mesh::InitMesh()
{
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), &m_vertices.at(0), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(), &m_indices.at(0), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

GLuint& Mesh::GetVBO()
{
	return m_vbo;
}

GLuint& Mesh::GetVAO()
{
	return m_vao;
}

GLuint & Mesh::GetEBO()
{
	return m_ebo;
}

std::vector<Vertex>& Mesh::GetVertices()
{
	return m_vertices;
}

std::vector<GLuint>& Mesh::GetIndices()
{
	return m_indices;
}
