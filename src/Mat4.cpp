#include "Mat4.h"

#include "MathShared.h"

#include "Vec4.h"
#include "Vec3.h"

using namespace Gyvr::Math;

#pragma region Constructors & Destructor
Mat4::Mat4(const Vec4& p_vec4)
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		for (uint8_t j = 0; j < 4; ++j)
		{
			if (i == j)
			{
				if (i == 0)
				{
					this->data[i][j] = p_vec4.x;
				}
				else if (i == 1)
				{
					this->data[i][j] = p_vec4.y;
				}
				else if (i == 2)
				{
					this->data[i][j] = p_vec4.z;
				}
				else if (i == 3)
				{
					this->data[i][j] = p_vec4.w;
				}
			}
		}
	}
}

Mat4::Mat4(const Mat4 & p_mat4)
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		for (uint8_t j = 0; j < 4; ++j)
		{
			data[i][j] = p_mat4.data[i][j];
		}
	}
}

Mat4::Mat4()
{
	SetIdentity();
}
#pragma endregion

#pragma region Overload
Mat4 Mat4::operator*(const Mat4& p_other)
{
	Mat4 toReturn;

	for (uint8_t row = 0; row < 4; ++row)
	{
		for (uint8_t col = 0; col < 4; ++col)
		{
			float value = 0;
			for (uint8_t u = 0; u < 4; ++u)
			{
				value += data[row][u] * p_other.data[u][col];
			}
			toReturn.data[row][col] = value;
		}
	}
	return toReturn;
}

Vec4 Mat4::operator*(const Vec4& p_other) const
{
	float multVec = 0;
	Vec4 multiply;
	for (uint8_t i = 0; i < 4; i++)
	{
		{
			multVec += this->data[i][0] * p_other.x;
			multVec += this->data[i][1] * p_other.y;
			multVec += this->data[i][2] * p_other.z;
			multVec += this->data[i][3] * p_other.w;
		}
		if (i == 0)
		{
			multiply.x = multVec;
		}
		else if (i == 1)
		{
			multiply.y = multVec;
		}
		else if (i == 2)
		{
			multiply.z = multVec;
		}
		else if (i == 3)
		{
			multiply.w = multVec;
		}
		multVec = 0;
	}
	return multiply;
}
#pragma endregion

Mat4 Mat4::CreatePerspective(const float p_fov, const float p_aspectRatio, const float p_zNear, const float p_zFar)
{
	const float tangent = tanf(p_fov / 2 * DEG_TO_RAD);
	const float height = p_zNear * tangent;
	const float width = height * p_aspectRatio;
	return CreateFrustum(-width, width, -height, height, p_zNear, p_zFar);
}

Mat4 Mat4::CreateFrustum(const float p_left, const float p_right, const float p_bottom, const float p_top, const float p_zNear, const float p_zFar)
{
	const float maxView = 2.0f * p_zNear;
	const float width = p_right - p_left;
	const float height = p_top - p_bottom;
	const float zRange = p_zFar - p_zNear;
	Mat4 Frustum;
	Frustum.data[0][0] = maxView / width;
	Frustum.data[1][1] = maxView / height;
	Frustum.data[2][0] = (p_right + p_left) / width;
	Frustum.data[2][1] = (p_top + p_bottom) / height;
	Frustum.data[2][2] = (-p_zFar - p_zNear) / zRange;
	Frustum.data[2][3] = -1.0f;
	Frustum.data[3][2] = (-maxView * p_zFar) / zRange;
	Frustum.data[3][3] = 0.0f;
	return Frustum;
}

Mat4 Mat4::CreateInverse()
{
	const float cof0 = GetMinor(data[1][1], data[2][1], data[3][1], data[1][2], data[2][2], data[3][2], data[1][3], data[2][3], data[3][3]);
	const float cof1 = GetMinor(data[0][1], data[2][1], data[3][1], data[0][2], data[2][2], data[3][2], data[0][3], data[2][3], data[3][3]);
	const float cof2 = GetMinor(data[0][1], data[1][1], data[3][1], data[0][2], data[1][2], data[3][2], data[0][3], data[1][3], data[3][3]);
	const float cof3 = GetMinor(data[0][1], data[1][1], data[2][1], data[0][2], data[1][2], data[2][2], data[0][3], data[1][3], data[2][3]);

	const float det = data[0][0] * cof0 - data[1][0] * cof1 + data[2][0] * cof2 - data[3][0] * cof3;
	if (fabs(det) <= EPSILON)
		return Identity();

	const float cof4 = GetMinor(data[1][0], data[2][0], data[3][0], data[1][2], data[2][2], data[3][2], data[1][3], data[2][3], data[3][3]);
	const float cof5 = GetMinor(data[0][0], data[2][0], data[3][0], data[0][2], data[2][2], data[3][2], data[0][3], data[2][3], data[3][3]);
	const float cof6 = GetMinor(data[0][0], data[1][0], data[3][0], data[0][2], data[1][2], data[3][2], data[0][3], data[1][3], data[3][3]);
	const float cof7 = GetMinor(data[0][0], data[1][0], data[2][0], data[0][2], data[1][2], data[2][2], data[0][3], data[1][3], data[2][3]);

	const float cof8 = GetMinor(data[1][0], data[2][0], data[3][0], data[1][1], data[2][1], data[3][1], data[1][3], data[2][3], data[3][3]);
	const float cof9 = GetMinor(data[0][0], data[2][0], data[3][0], data[0][1], data[2][1], data[3][1], data[0][3], data[2][3], data[3][3]);
	const float cof10 = GetMinor(data[0][0], data[1][0], data[3][0], data[0][1], data[1][1], data[3][1], data[0][3], data[1][3], data[3][3]);
	const float cof11 = GetMinor(data[0][0], data[1][0], data[2][0], data[0][1], data[1][1], data[2][1], data[0][3], data[1][3], data[2][3]);

	const float cof12 = GetMinor(data[1][0], data[2][0], data[3][0], data[1][1], data[2][1], data[3][1], data[1][2], data[2][2], data[3][2]);
	const float cof13 = GetMinor(data[0][0], data[2][0], data[3][0], data[0][1], data[2][1], data[3][1], data[0][2], data[2][2], data[3][2]);
	const float cof14 = GetMinor(data[0][0], data[1][0], data[3][0], data[0][1], data[1][1], data[3][1], data[0][2], data[1][2], data[3][2]);
	const float cof15 = GetMinor(data[0][0], data[1][0], data[2][0], data[0][1], data[1][1], data[2][1], data[0][2], data[1][2], data[2][2]);

	const float detInv = 1.0f / det;
	Mat4 inverse;

	inverse.data[0][0] = detInv * cof0;
	inverse.data[1][0] = -detInv * cof4;
	inverse.data[2][0] = detInv * cof8;
	inverse.data[3][0] = -detInv * cof12;
	inverse.data[0][1] = -detInv * cof1;
	inverse.data[1][1] = detInv * cof5;
	inverse.data[2][1] = -detInv * cof9;
	inverse.data[3][1] = detInv * cof13;
	inverse.data[0][2] = detInv * cof2;
	inverse.data[1][2] = -detInv * cof6;
	inverse.data[2][2] = detInv * cof10;
	inverse.data[3][2] = -detInv * cof14;
	inverse.data[0][3] = -detInv * cof3;
	inverse.data[1][3] = detInv * cof7;
	inverse.data[2][3] = -detInv * cof11;
	inverse.data[3][3] = detInv * cof15;

	return inverse;
}

Mat4 Mat4::CreateTranspose()
{
	Mat4 Transpose;
	for (uint16_t i = 0; i < 4; i++)
	{
		for (uint16_t j = 0; j < 4; j++)
		{
			Transpose.data[i][j] = data[j][i];
		}
	}
	return Transpose;
}

Mat4 Mat4::CreateTranslation(const float p_x, const float p_y, const float p_z)
{
	Mat4 Translate;
	Translate.data[0][3] = p_x;
	Translate.data[1][3] = p_y;
	Translate.data[2][3] = p_z;
	return Translate;
}

Mat4 Mat4::CreateView(const float p_eyeX, const float p_eyeY, const float p_eyeZ, const float p_lookX, const float p_lookY, const float p_lookZ, const float p_upX, const float p_upY, const float p_upZ)
{
	const Vec3 eye(p_eyeX, p_eyeY, p_eyeZ);
	const Vec3 look(p_lookX, p_lookY, p_lookZ);
	const Vec3 up(p_upX, p_upY, p_upZ);
	const Vec3 eye_look(eye - look);
	const Vec3 n(eye_look / eye_look.GetMagnitude());
	const Vec3 UpXn(up.Cross(n));
	const Vec3 u(UpXn / UpXn.GetMagnitude());
	const Vec3 v(n.Cross(u));
	Mat4 View;
	View.data[0][0] = u.x;
	View.data[0][1] = u.y;
	View.data[0][2] = u.z;
	View.data[0][3] = -eye.dot(u);
	View.data[1][0] = v.x;
	View.data[1][1] = v.y;
	View.data[1][2] = v.z;
	View.data[1][3] = -eye.dot(v);
	View.data[2][0] = n.x;
	View.data[2][1] = n.y;
	View.data[2][2] = n.z;
	View.data[2][3] = -eye.dot(n);
	return View;
}

Mat4 Mat4::CreateRotation(const float p_xAngle, const float p_yAngle, const float p_zAngle)
{
	Mat4 xRot, yRot, zRot;
	const float xRad = static_cast<float>(p_xAngle * M_PI / 180.0f);
	const float yRad = static_cast<float>(p_yAngle * M_PI / 180.0f);
	const float zRad = static_cast<float>(p_zAngle * M_PI / 180.0f);

	xRot.data[1][1] = cos(xRad);
	xRot.data[1][2] = -sin(xRad);
	xRot.data[2][1] = sin(xRad);
	xRot.data[2][2] = cos(xRad);

	yRot.data[0][0] = cos(yRad);
	yRot.data[0][2] = -sin(yRad);
	yRot.data[2][0] = sin(yRad);
	yRot.data[2][2] = cos(yRad);

	zRot.data[0][0] = cos(zRad);
	zRot.data[0][1] = -sin(zRad);
	zRot.data[1][0] = sin(zRad);
	zRot.data[1][1] = cos(zRad);

	return xRot * yRot * zRot;
}

Mat4 Mat4::CreateScale(const float p_xScale, const float p_yScale, const float p_zScale)
{
	Mat4 Scale;
	Scale.data[0][0] = p_xScale;
	Scale.data[1][1] = p_yScale;
	Scale.data[2][2] = p_zScale;

	return Scale;
}

Vec3 Mat4::ConvertToScreen(const Vec3& p_vector, const float p_width, const float p_height)
{
	const float widthHalf = p_width / 2.0f;
	const float heightHalf = p_height / 2.0f;
	return Vec3(((p_vector.x / 5.0f) + 1) * widthHalf, p_height - ((p_vector.y / 5.0f) + 1) * heightHalf, p_vector.z);
}

Vec3 Mat4::ScreenToView(const Vec3 & p_vector, const float p_width, const float p_height)
{
	const float widthHalf = p_width / 2.0f;
	const float heightHalf = p_height / 2.0f;
	return Vec3(((p_vector.x / widthHalf) - 1) * 5.0f, ((((p_vector.y - p_height)  * -1) / heightHalf) - 1) * 5.0f, p_vector.z);
}

void Mat4::SetNull()
{
	for (auto & row : data)
		for (auto& col : row)
			col = 0;
}

Mat4 Mat4::Identity()
{
	Mat4 identity;
	return identity;
}

void Mat4::SetIdentity()
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		for (uint8_t j = 0; j < 4; ++j)
		{
			this->data[i][j] = i == j;
		}
	}
}

float Mat4::Determinant()
{
	return	  data[0][0]
		* GetMinor(data[1][1], data[2][1], data[3][1], data[1][2], data[2][2], data[3][2], data[1][3], data[2][3], data[3][3])
		- data[1][0] * GetMinor(data[0][1], data[2][1], data[3][1], data[0][2], data[2][2], data[3][2], data[0][3], data[2][3], data[3][3])
		+ data[2][0] * GetMinor(data[0][1], data[1][1], data[3][1], data[0][2], data[1][2], data[3][2], data[0][3], data[1][3], data[3][3])
		- data[3][0] * GetMinor(data[0][1], data[1][1], data[2][1], data[0][2], data[1][2], data[2][2], data[0][3], data[1][3], data[2][3]);
}

float Mat4::GetMinor(const float p_m0, const float p_m1, const float p_m2, const float p_m3, const float p_m4, const float p_m5, const float p_m6, const float p_m7, const float p_m8)
{
	return	  p_m0 * (p_m4 * p_m8 - p_m5 * p_m7)
		- p_m1 * (p_m3 * p_m8 - p_m5 * p_m6)
		+ p_m2 * (p_m3 * p_m7 - p_m4 * p_m6);
}

void Mat4::DisplayData() const
{
	for (auto row : data)
	{
		for (uint16_t col = 0; col < 4; ++col)
		{
			std::cout << row[col] << " ";
		}
		std::cout << std::endl;
	}
}