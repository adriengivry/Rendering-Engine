#pragma once

#include "ABehaviour.h"

namespace Gyvr
{
	namespace Object
	{
		/*
		* Component to set light
		*/
		class Light : public ABehaviour
		{
		public:
			Light();
			~Light() = default;
		};
	}
}