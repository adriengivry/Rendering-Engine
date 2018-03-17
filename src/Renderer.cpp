#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Window.h"
#include "SharedContext.h"

using namespace Gyvr::Core::System;

Renderer::Renderer(Gyvr::Util::SharedContext& p_sharedContext)
	: m_sharedContext(p_sharedContext)
{
	Renderer::Setup();
}

Renderer::~Renderer() { Renderer::Close(); }

void Renderer::Setup() {}
void Renderer::Close() {}

void Renderer::Update()
{
	m_sharedContext.window->GetDriver()->ClearScreen();

	if (m_sharedContext.sceneManager->HasCurrentScene())
	{
		auto& sceneToRender = m_sharedContext.sceneManager->GetCurrentScene();
		RenderGameObject(sceneToRender.GetRoot());
	}

	m_sharedContext.window->GetDevice()->SwapBuffers();
}

void Renderer::RenderGameObject(Gyvr::Object::GameObject& p_gameObject)
{
	p_gameObject.Draw();
	p_gameObject.Update();

	for (const auto& child : p_gameObject.GetChilds())
	{
		RenderGameObject(*child);
	}
}
