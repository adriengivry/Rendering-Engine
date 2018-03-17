#include "MeshRenderer.h"

Gyvr::Object::MeshRenderer::MeshRenderer()
{
	SetName("MeshRenderer");
	m_mesh = nullptr;
}

void Gyvr::Object::MeshRenderer::SetMesh(Gyvr::Resource::Mesh * p_mesh)
{
	m_mesh = p_mesh;
}

void Gyvr::Object::MeshRenderer::Draw()
{
	if (m_mesh)
	{
		glBindVertexArray(m_mesh->GetVAO());

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->GetEBO());

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_mesh->GetIndices().size()), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
}
