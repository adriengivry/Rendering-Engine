#pragma once

#include "ABehaviour.h"

namespace Gyvr
{
	namespace Object
	{
		/*
		* Camera component used to view the scene
		*/
		class Camera : public ABehaviour
		{
		public:
			Camera();
			~Camera() = default;

			void Update();
		};
	}
}