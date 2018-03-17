#pragma once

#include "Vec3.h"
#include "AComponent.h"

namespace Gyvr
{
	namespace Object
	{
		/*
		* Position, rotation and scale of any GameObject
		*/
		class Transform : public AComponent
		{
		public:
			Transform();
			explicit Transform(const Math::Vec3& p_position);
			explicit Transform(const Math::Vec3& p_position, const Gyvr::Math::Vec3& p_rotation);
			explicit Transform(const Math::Vec3& p_position, const Gyvr::Math::Vec3& p_rotation, const Gyvr::Math::Vec3& p_scale);
			~Transform() = default;

			Gyvr::Math::Vec3& GetPosition();
			Gyvr::Math::Vec3& GetRotation();
			Gyvr::Math::Vec3& GetScale();

			void SetPosition(const Gyvr::Math::Vec3& p_position);
			void SetRotation(const Gyvr::Math::Vec3& p_rotation);
			void SetScale(const Gyvr::Math::Vec3& p_scale);

			void Translate(const Gyvr::Math::Vec3& p_translate);
			void Rotate(const Gyvr::Math::Vec3& p_rotate);
			void Scale(const Gyvr::Math::Vec3& p_scale);

		private:
			Gyvr::Math::Vec3 m_position;
			Gyvr::Math::Vec3 m_rotation;
			Gyvr::Math::Vec3 m_scale;
		};
	}
}
