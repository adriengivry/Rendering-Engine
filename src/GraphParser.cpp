#include "GraphParser.h"
#include "SceneManager.h"

using namespace Gyvr::Util;
using namespace Gyvr::Object;
using namespace tinyxml2;

Gyvr::Util::GraphParser::GraphParser(Gyvr::Util::SharedContext & p_sharedContext)
	: m_sharedContext(p_sharedContext)
{
	ResetErrorsAndWarnings();
}

void Gyvr::Util::GraphParser::ResetErrorsAndWarnings()
{
	m_errors = 0;
	m_warnings = 0;
}

void Gyvr::Util::GraphParser::AddError()
{
	m_errors += 1;
}

void Gyvr::Util::GraphParser::AddWarning()
{
	m_warnings += 1;
}

void Gyvr::Util::GraphParser::ImportFromXML(const std::string& p_filename, Gyvr::Core::System::SceneManager& p_sceneManager, Gyvr::Object::GameObject& p_root)
{
	ResetErrorsAndWarnings();

	std::string filepath = GET_STRING(GENERAL, "scene_graph_path") + p_filename;

	Gyvr::Core::Debug::Log::Process("Start import from XML (Source: " + filepath + ")", Gyvr::Core::Debug::Log::LogLevel::LOG_INFO);
	
	XMLDocument doc;
	doc.LoadFile(filepath.c_str());
	
	auto* gameobjects = doc.FirstChildElement("gameobjects");;
	auto* gameobject = gameobjects->FirstChildElement("gameobject");
	while (gameobject)
	{
		ImportGameObject(p_sceneManager, doc, *gameobject, &p_root);
		gameobject = gameobject->NextSiblingElement("gameobject");
	}

	std::string exportResult;
	if (m_errors > 0)
		exportResult = "Failed to import the whole scene from XML ";
	else
		exportResult = "Import scene from XML completed ";
	exportResult += "(Warnings: " + std::to_string(m_warnings) + ", Errors:" + std::to_string(m_errors) + ")";
	Gyvr::Core::Debug::Log::Process(exportResult, Gyvr::Core::Debug::Log::LogLevel::LOG_INFO);
}

void Gyvr::Util::GraphParser::ImportGameObject(Gyvr::Core::System::SceneManager& p_sceneManager, XMLDocument& p_doc, XMLElement& p_gameObject, Gyvr::Object::GameObject* p_parent)
{
	std::string gameObjectName(p_gameObject.FirstChildElement("name")->GetText());

	Gyvr::Object::GameObject& realGameObject = p_parent ? p_sceneManager.CreateEmptyGameObject(*p_parent, gameObjectName) : p_sceneManager.CreateEmptyGameObject(gameObjectName);

	auto* components = p_gameObject.FirstChildElement("components");
	if (components)
	{
		auto* comp = components->FirstChildElement("component");
		while (comp)
		{
			ImportComponent(p_doc, comp, realGameObject);
			comp = comp->NextSiblingElement("component");
		}
	}

	auto* childs = p_gameObject.FirstChildElement("childs");
	if (childs)
	{
		auto* gameobject = childs->FirstChildElement("gameobject");
		while (gameobject)
		{
			ImportGameObject(p_sceneManager, p_doc, *gameobject, &realGameObject);
			gameobject = gameobject->NextSiblingElement("gameobject");
		}
	}
}

void Gyvr::Util::GraphParser::ImportComponent(tinyxml2::XMLDocument & p_doc, tinyxml2::XMLElement * p_component, Object::GameObject & p_owner)
{
	std::string compName(p_component->FirstChildElement("name")->GetText());

	if (compName == "Transform")
	{
		p_owner.AddComponent<Transform>();
		auto transform = p_owner.GetComponent<Transform>();

		{
			auto* position = p_component->FirstChildElement("position");
			float x = std::stof(position->FirstChildElement("x")->GetText());
			float y = std::stof(position->FirstChildElement("y")->GetText());
			float z = std::stof(position->FirstChildElement("z")->GetText());
			transform->SetPosition(Math::Vec3(x, y, z));
		}

		{
			auto* rotation = p_component->FirstChildElement("rotation");
			float x = std::stof(rotation->FirstChildElement("x")->GetText());
			float y = std::stof(rotation->FirstChildElement("y")->GetText());
			float z = std::stof(rotation->FirstChildElement("z")->GetText());
			transform->SetRotation(Math::Vec3(x, y, z));
		}

		{
			auto* scale = p_component->FirstChildElement("scale");
			float x = std::stof(scale->FirstChildElement("x")->GetText());
			float y = std::stof(scale->FirstChildElement("y")->GetText());
			float z = std::stof(scale->FirstChildElement("z")->GetText());
			transform->SetScale(Math::Vec3(x, y, z));
		}
	}
	else if (compName == "MeshRenderer")
	{
		p_owner.AddComponent<MeshRenderer>();
		std::string meshName = p_component->FirstChildElement("meshName")->GetText();
		auto meshRenderer = p_owner.GetComponent<MeshRenderer>();
		if (m_sharedContext.meshManager->RequireResource(meshName))
			meshRenderer->SetMesh(m_sharedContext.meshManager->GetResource(meshName));
		else
		{
			Gyvr::Core::Debug::Log::Process("Mesh: " + meshName + " not found, check meshes.cfg", Gyvr::Core::Debug::Log::LogLevel::LOG_ERROR);
			AddError();
		}
	}
	else if (compName == "Light")
	{

	}
	else if (compName == "Camera")
	{

	}
	
}
