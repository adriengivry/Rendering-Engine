#include "Engine.h"

using namespace Gyvr::Core::System;

Engine::Engine() { Engine::Setup(); }

Engine::Engine(char**& p_args) 
{
	m_sharedContext.engineInfo.launchedFromUnity = p_args[1] != nullptr;
	if (m_sharedContext.engineInfo.launchedFromUnity)
	{
		m_sharedContext.engineInfo.unityCurrentScene = p_args[1];
	}
	Engine::Setup();
}
Engine::~Engine() { Engine::Close(); }

void Engine::Update() {}
void Engine::Close() {}

void Engine::Quit()
{
	m_quit = true;
}

bool Engine::IsRunning() const
{
	return m_quit ? false : m_window->GetDriver()->IsActive() && m_window->GetDevice()->IsActive();
}

void Engine::PollEvents() const
{
	m_inputManager->Update();
	Context::Device::PollEvents();
}

void Engine::Draw() const
{
	m_renderer->Update();
}

std::shared_ptr<SceneManager> Engine::GetSceneManager() const
{
	return m_sceneManager;
}

std::shared_ptr<InputManager> Engine::GetInputManager() const
{
	return m_inputManager;
}

std::shared_ptr<TextureManager> Engine::GetTextureManager() const
{
	return m_textureManager;
}

std::shared_ptr<MeshManager> Gyvr::Core::System::Engine::GetMeshManager() const
{
	return m_meshManager;
}

void Engine::Setup()
{
	m_quit = false;

	m_textureManager = std::make_shared<Resource::TextureManager>();
	m_sharedContext.textureManager = m_textureManager;

	m_meshManager = std::make_shared<Resource::MeshManager>();
	m_sharedContext.meshManager = m_meshManager;

	m_window = std::make_shared<Window>(m_sharedContext);
	m_sharedContext.window = m_window;

	m_sceneManager = std::make_shared<SceneManager>(m_sharedContext);
	m_sharedContext.sceneManager = m_sceneManager;

	m_inputManager = std::make_shared<InputManager>(m_sharedContext);
	m_sharedContext.eventManager = m_inputManager;

	m_renderer = std::make_shared<Renderer>(m_sharedContext);
	m_sharedContext.renderer = m_renderer;

	Debug::Log::Process("Engine setup completed", Debug::Log::LogLevel::LOG_INFO);
}
