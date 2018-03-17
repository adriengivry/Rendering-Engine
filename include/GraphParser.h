#pragma once

#include "GameObject.h"
#include "ConfigLoader.h"
#include "tinyxml2.h"
#include "ConfigLoader.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "Camera.h"
#include "MeshManager.h"
#include "SharedContext.h"

namespace Gyvr
{
	namespace System
	{
		namespace Core
		{
			class SceneManager;
		}
	}
	namespace Util
	{
		/*
		* A simple class to load and export scene graphs
		*/
		class GraphParser
		{
		public:
			GraphParser(Gyvr::Util::SharedContext& p_sharedContext);
			~GraphParser() = default;

			void ResetErrorsAndWarnings();

			void AddError();
			void AddWarning();

			void ImportFromXML(const std::string& p_filename, Gyvr::Core::System::SceneManager& p_sceneManager, Gyvr::Object::GameObject& p_root);
			void ImportGameObject(Gyvr::Core::System::SceneManager& p_sceneManager, tinyxml2::XMLDocument& p_doc, tinyxml2::XMLElement& p_gameObject, Gyvr::Object::GameObject* p_parent = nullptr);

			void ImportComponent(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLElement* p_component, Object::GameObject& p_owner);

		private:
			Gyvr::Util::SharedContext& m_sharedContext;
			uint16_t m_errors;
			uint16_t m_warnings;
		};
	}
}

