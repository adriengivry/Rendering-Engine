#pragma once

#include <memory>
#include <string>

namespace Gyvr
{
	namespace Core
	{
		namespace System
		{
			/*
			* Prevent multiple inclusion. If a class hold a SharedContext reference and wants to access to FooClass complete informations,
			* the "FooClass.h" must be included in the .cpp of the class holding the SharedContext reference
			*/
			class Window;
			class SceneManager;
			class InputManager;
			class Renderer;
		}
	}

	namespace Resource
	{
		class TextureManager;
		class MeshManager;
	}
}

namespace Gyvr
{
	namespace Util
	{
		/*
		* The ISharedData struct is an interface that explain how a sharedData must be constructed
		*/
		struct ISharedData
		{
			virtual ~ISharedData() = default;
			virtual void Setup() = 0;
		};

		/*
		* The EngineInfo is a SharedData that contains informations about the Engine. It is used as an attribute of SharedContext
		*/
		struct EngineInfo : ISharedData
		{
			EngineInfo() { EngineInfo::Setup(); }
			void Setup() override
			{
				launchedFromUnity = false;
			}

			bool launchedFromUnity;
			std::string unityCurrentScene;
		};

		/*
		* The SharedContext is a set of data that can be shared between class in order to allow some classes to get informations from other classes.
		* It also includes other struct (ISharedData) that are kind of boxes to organize informations
		*/
		struct SharedContext : ISharedData
		{
			SharedContext() { SharedContext::Setup(); }
			void Setup() override
			{

			}

			EngineInfo engineInfo;

			std::shared_ptr<Gyvr::Core::System::Window> window;
			std::shared_ptr<Gyvr::Core::System::SceneManager> sceneManager;
			std::shared_ptr<Gyvr::Core::System::InputManager> eventManager;
			std::shared_ptr<Gyvr::Core::System::Renderer> renderer;
			std::shared_ptr<Gyvr::Resource::TextureManager> textureManager;
			std::shared_ptr<Gyvr::Resource::MeshManager> meshManager;
		};
	}
}