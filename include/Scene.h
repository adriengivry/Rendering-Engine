#pragma once

#include <memory>
#include <iostream>

#include "AObject.h"
#include "SharedContext.h"
#include "GameObject.h"

namespace Gyvr
{
	namespace Object
	{
		/*
		 * Class that contain a root gameObject which can have some childs
		 */
		class Scene : public AObject
		{
		public:
			explicit Scene(Gyvr::Util::SharedContext& p_sharedContext);
			~Scene() = default;

			Gyvr::Object::GameObject& GetRoot() const;

		private:
			Gyvr::Util::SharedContext & m_sharedContext;
			std::shared_ptr<GameObject> m_root;
		};
	}
}
