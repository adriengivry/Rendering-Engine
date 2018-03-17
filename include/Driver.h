#pragma once

#include <GL/glew.h>

#include "IContext.h"
#include "Assertion.h"

namespace Gyvr
{
	namespace Core
	{
		namespace System
		{
			namespace Context
			{
				/*
				* The Driver context handle the OpenGL Context. Actually it uses GLEW Libarary
				*/
				class Driver : public IContext
				{
				public:
					Driver();
					virtual ~Driver() = default;
					void InitContext() override;
					void CloseContext() override {}
					bool IsActive() override;

					void ClearScreen();

				private:
					bool m_active;
				};
			}
		}
	}
}
