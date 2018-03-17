#pragma once

namespace Gyvr
{
	namespace Math
	{
		/*
		* Implementation of the mathematic 2 coordinates vector
		*/
		struct Vec2
		{
			float x;
			float y;
			explicit Vec2(float p_x = 0, float p_y = 0);
			Vec2(const Vec2& p_other);
			float GetMagnitude() const;
			void Normalize();
			float Cross(const Vec2& p_other)const;
			Vec2 operator+(const Vec2& p_other) const;
			Vec2 operator-(const Vec2& p_other) const;
			Vec2 operator*(float p_scale) const;
			float operator*(const Vec2& p_other) const;
		};
	}
}