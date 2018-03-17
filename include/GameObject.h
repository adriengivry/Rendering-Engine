#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "AObject.h"
#include "AComponent.h"
#include "Scene.h"
#include "Transform.h"
#include "Light.h"
#include "Camera.h"
#include "SharedContext.h"
#include "Log.h"

namespace Gyvr
{
	namespace Object
	{
		/*
		 * A GameObject is an Object that can be placed in the Scene. It contains differents components
		 */
		class GameObject : public AObject
		{
		public:
			explicit GameObject(Gyvr::Util::SharedContext& p_sharedContext);
			explicit GameObject(Gyvr::Util::SharedContext& p_sharedContext, GameObject& p_parent, const std::string& p_name = "GameObject");
			virtual ~GameObject() = default;

			template<typename Class, typename...Args>
			void AddComponent(Args... args);
			void AddComponent(const std::string& p_type);
			void AddChild(GameObject& p_child);

			template<typename Class>
			std::shared_ptr<Class> GetComponent();
			std::unordered_map<const std::type_info*, std::shared_ptr<AComponent>>& GetComponents();
			std::vector <std::shared_ptr<GameObject>>& GetChilds();
			GameObject& GetParent() const;
			bool HasParent() const;

			void Setup();

			void Draw();
			void Update();

			void SetParent(GameObject& p_parent);

			Gyvr::Util::SharedContext& m_sharedContext;
			std::unordered_map<const std::type_info*, std::shared_ptr<AComponent>> m_components;
			GameObject* m_parent;
			std::vector<std::shared_ptr<GameObject>> m_childs;
		};

		template <typename Class, typename ... Args>
		void GameObject::AddComponent(Args... args)
		{
			auto newComp = std::make_shared<Class>(std::forward<Args>(args)...);
			m_components[&typeid(*newComp)] = newComp;
			m_components[&typeid(*newComp)]->SetOwner(*this);
		}

		template <typename Class>
		std::shared_ptr<Class> GameObject::GetComponent()
		{
			std::shared_ptr<Class> result(nullptr);

			if (m_components.count(&typeid(Class)) != 0)
				result = std::dynamic_pointer_cast<Class>(m_components[&typeid(Class)]);

			return result;
		}
	}
}
