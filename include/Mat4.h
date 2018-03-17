#pragma once

#include "Vec4.h"

namespace Gyvr
{
	namespace Math
	{
		/*
		 * Implementation of the mathematic 4*4 matrix
		 */
		struct Mat4
		{
			float data[4][4];

			Mat4();
			explicit Mat4(const Vec4& p_vec4);
			Mat4(const Mat4& p_mat4);
			Mat4 operator*(const Mat4& p_other);
			Vec4 operator*(const Vec4& p_other) const;

			static Mat4 CreatePerspective(float p_fov, float p_aspectRatio, float p_zNear, float p_zFar);
			static Mat4 CreateTranslation(float p_x, float p_y, float p_z);
			static Mat4 CreateView(float p_eyeX, float p_eyeY, float p_eyeZ, float p_lookX, float p_lookY, float p_lookZ, float p_upX, float p_upY, float p_upZ);
			static Mat4 CreateRotation(float p_xAngle, float p_yAngle, float p_zAngle);
			static Mat4 CreateScale(float p_xScale, float p_yScale, float p_zScale);
			static Mat4 CreateFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_zNear, float p_zFar);
			Mat4 CreateInverse();
			Mat4 CreateTranspose();
			static Vec3 ConvertToScreen(const Vec3& p_vector, float p_width, float p_height);
			static Vec3 ScreenToView(const Vec3& p_vector, float p_width, float p_height);
			void SetNull();
			static Mat4 Identity();
			void SetIdentity();
			float Determinant();
			static float GetMinor(float p_m0, float p_m1, float p_m2, float p_m3, float p_m4, float p_m5, float p_m6, float p_m7, float p_m8);
			void DisplayData() const;
		};
	}
}