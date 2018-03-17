#include "SceneManager.h"

using namespace Gyvr::Core::System;
using namespace Gyvr::Object;

SceneManager::SceneManager(Gyvr::Util::SharedContext& p_sharedContext)
	: m_sharedContext(p_sharedContext)
{
	SceneManager::Setup();
}

void SceneManager::Update() {}
void SceneManager::Close() {}

void SceneManager::Setup()
{
	m_currentScene = nullptr;
	m_graphParser = std::make_unique<Gyvr::Util::GraphParser>(m_sharedContext);
}

void SceneManager::SetCurrentScene(const std::string& p_sceneName)
{
	for (const auto& scene : m_scenes)
		if (scene.first == p_sceneName)
			m_currentScene = scene.second;
}

Scene& SceneManager::CreateScene(const std::string& p_sceneName, const bool p_setCurrent)
{
	auto newScene = std::make_shared<Scene>(m_sharedContext);
	newScene->SetName(p_sceneName);

	m_scenes.insert_or_assign(p_sceneName, newScene);
	if (p_setCurrent)
		m_currentScene = std::shared_ptr<Scene>(newScene);

	return *newScene.get();
}

Scene& Gyvr::Core::System::SceneManager::CreateSceneFromUnity(const std::string& p_sceneName, const bool p_setCurrent)
{
	if (m_sharedContext.engineInfo.launchedFromUnity)
	{
		std::string sceneName;
		if (p_sceneName == "")
			sceneName = m_sharedContext.engineInfo.unityCurrentScene;
		return CreateFromXML("unity_scenes/" + m_sharedContext.engineInfo.unityCurrentScene + ".xml", sceneName, p_setCurrent);
	}
	else
	{
		Debug::Log::Process("No unity scene to load, an empty scene get generated", Debug::Log::LogLevel::LOG_ERROR);
		return CreateScene(p_sceneName, p_setCurrent);
	}
}

Scene& Gyvr::Core::System::SceneManager::CreateFromXML(const std::string& p_filename, const std::string& p_sceneName, const bool p_setCurrent)
{
	Scene& scene = CreateScene(p_sceneName, p_setCurrent);

	m_graphParser->ImportFromXML(p_filename, *this, scene.GetRoot());

	return scene;
}


GameObject& SceneManager::CreateEmptyGameObject(const std::string& p_name) const
{
	GameObject* gameObject = new GameObject(m_sharedContext, m_currentScene->GetRoot(), p_name);
	return *gameObject;
}

GameObject& SceneManager::CreateEmptyGameObject(GameObject& p_parent, const std::string& p_name) const
{
	GameObject* gameObject = new GameObject(m_sharedContext, p_parent, p_name);
	return *gameObject;
}

Scene& SceneManager::GetCurrentScene() const
{
	return *m_currentScene.get();
}

bool Gyvr::Core::System::SceneManager::HasCurrentScene() const
{
	if (m_currentScene)
		return true;
	else
		return false;
}