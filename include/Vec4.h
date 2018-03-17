#pragma once

#include "Vec3.h"

namespace Gyvr
{
	namespace Math
	{
		/*
		* Implementation of the mathematic 4 coordinates vector
		*/
		struct Vec4
		{
			float x;
			float y;
			float z;
			float w;
			explicit Vec4(const Vec3& p_vec3, float p_w = 1.0f);
			explicit Vec4(float p_x = 0, float p_y = 0, float p_z = 0, float p_w = 1.0f);
			void Homogenize();
			float Getmagnitude() const;
			void Normalize();
			Vec4 Cross(const Vec4& p_other) const;
			Vec4 operator+(const Vec4& p_other) const;
			float operator*(const Vec4& p_other) const;
			Vec4 operator*(float p_scale) const;
			Vec4& operator=(const Vec4& p_other);
			Vec4& operator/=(float p_scale);
		};
	}
}