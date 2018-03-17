#pragma once

#include "IManager.h"
#include "SharedContext.h"
#include "GameObject.h"

namespace Gyvr
{
	namespace Core
	{
		namespace System
		{
			/*
			* The renderer is pretty usefull to print things on the screen !
			*/
			class Renderer : public IManager
			{
			public:
				explicit Renderer(Util::SharedContext& p_sharedContext);
				~Renderer();

				void Setup() override;
				void Update() override;
				void Close() override;

				static void RenderGameObject(Gyvr::Object::GameObject& p_gameObject);

			private:
				Gyvr::Util::SharedContext& m_sharedContext;
			};
		}
	}
}
