#pragma once

#include "IManager.h"
#include "SharedContext.h"
#include "Window.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Log.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "Renderer.h"

namespace Gyvr
{
	namespace Core
	{
		namespace System
		{
			using namespace Gyvr::Resource;

			/*
			* The Engine is the main class of the program, it calls everyone methods (Create Window, call Renderer update, etc...)
			*/
			class Engine : public IManager
			{
			public:
				Engine();
				Engine(char**& p_args);
				~Engine();

			private:
				void Setup() override;
				void Update() override;
				void Close() override;

			public:
				void Quit();
				bool IsRunning() const;
				void PollEvents() const;
				void Draw() const;

				std::shared_ptr<SceneManager> GetSceneManager() const;
				std::shared_ptr<InputManager> GetInputManager() const;
				std::shared_ptr<TextureManager> GetTextureManager() const;
				std::shared_ptr<MeshManager> GetMeshManager() const;

			private:
				Util::SharedContext m_sharedContext;
				
				std::shared_ptr<Window> m_window;
				std::shared_ptr<SceneManager> m_sceneManager;
				std::shared_ptr<InputManager> m_inputManager;
				std::shared_ptr<Renderer> m_renderer;
				std::shared_ptr<TextureManager> m_textureManager;
				std::shared_ptr<MeshManager> m_meshManager;

				bool m_quit;
			};
		}
	}
}
