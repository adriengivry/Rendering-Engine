#pragma once

#include <memory>

#include "AObject.h"

namespace Gyvr
{
	namespace Object
	{
		class GameObject;

		/*
		* The base class for every components in GyvrEngine
		*/
		class AComponent : public AObject
		{
		public:
			AComponent();
			virtual ~AComponent() = default;

			void SetOwner(GameObject& p_owner);
			GameObject& GetOwner() const;

		protected:
			GameObject* m_owner = nullptr;
		};
	}
}

