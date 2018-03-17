#pragma once

namespace Gyvr
{
	namespace Math
	{
		/*
		* Implementation of the mathematic 3 coordinates vector
		*/
		struct Vec3
		{
			float x;
			float y;
			float z;
			explicit Vec3(float p_x = 0, float p_y = 0, float p_z = 0);
			Vec3(const Vec3& p_other);
			float GetMagnitude() const;
			void Normalize();
			float dot(const Vec3& p_other)const;
			Vec3 Cross(const Vec3& p_other)const;
			Vec3 operator+(const Vec3& p_other) const;
			Vec3 operator-(const Vec3& p_other) const;
			Vec3 operator*(float p_scale) const;
			Vec3 operator/(float p_scale) const;
			Vec3& operator=(const Vec3& p_other);
			Vec3& operator+=(const Vec3& p_other);
		};
	}
}