#pragma once

namespace Gyvr
{
	namespace Core
	{
		namespace System
		{
			namespace Context
			{
				/*
				 * Context interface to indicate how to implement a Context-based class
				 */
				class IContext
				{
				public:
					virtual ~IContext() = default;
					virtual void InitContext() = 0;
					virtual void CloseContext() = 0;
					virtual bool IsActive() = 0;
				};
			}
		}
	}
}