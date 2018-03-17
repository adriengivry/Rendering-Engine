#pragma once

#include "AComponent.h"

namespace Gyvr
{
	namespace Object
	{
		/*
		 * The base class for every components that can be enabled/disabled
		 */
		class ABehaviour : public AComponent
		{
		public:
			ABehaviour();
			virtual ~ABehaviour() = 0;
			bool IsActive() const;
			void SetActive(bool p_state);

		protected:
			bool m_active;
		};

		inline ABehaviour::~ABehaviour() = default;
	}
}