#pragma once

#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>

#include "IManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "SharedContext.h"
#include "ConfigLoader.h"
#include "GraphParser.h"
#include "Log.h"

namespace Gyvr
{
	namespace Core
	{
		namespace System
		{
			/*
			 * Manager to manipulate scenes
			 */
			class SceneManager : public IManager
			{
			public:
				explicit SceneManager(Gyvr::Util::SharedContext& p_sharedContext);
				~SceneManager() = default;

				void Setup() override;
				void Update() override;
				void Close() override;

				void SetCurrentScene(const std::string& p_sceneName);
				Object::Scene& CreateScene(const std::string& p_sceneName, bool p_setCurrent = true);
				Object::Scene& CreateSceneFromUnity(const std::string& p_sceneName = "", bool p_setCurrent = true);
				Object::GameObject& CreateEmptyGameObject(const std::string& p_name = "GameObject") const;
				Object::GameObject& CreateEmptyGameObject(Object::GameObject& p_parent, const std::string& p_name = "GameObject") const;
				Object::Scene& GetCurrentScene() const;

				bool HasCurrentScene() const;

				Object::Scene& CreateFromXML(const std::string& p_filename, const std::string& p_sceneName, bool p_setCurrent = true);

			private:
				Gyvr::Util::SharedContext & m_sharedContext;
				std::map<std::string, std::shared_ptr<Gyvr::Object::Scene>> m_scenes;
				std::shared_ptr<Gyvr::Object::Scene> m_currentScene;
				std::unique_ptr<Gyvr::Util::GraphParser> m_graphParser;
			};
		}
	}
}
