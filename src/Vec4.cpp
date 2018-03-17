#include "Vec4.h"

#include "MathShared.h"

using namespace Gyvr::Math;

#pragma region Constructors & Destructor
Vec4::Vec4(const Vec3& p_vec3, const float p_w)
{
	this->x = p_vec3.x;
	this->y = p_vec3.y;
	this->z = p_vec3.z;
	this->w = p_w;
}

Vec4::Vec4(const float p_x, const float p_y, const float p_z, const float p_w)
{
	this->x = p_x;
	this->y = p_y;
	this->z = p_z;
	this->w = p_w;
}
#pragma endregion

#pragma region Overload
Vec4 Vec4::operator+(const Vec4& p_other) const
{
	return Vec4(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z, this->z + p_other.z);
}

float Vec4::operator*(const Vec4 & p_other) const
{
	return (this->x * p_other.x + this->y * p_other.y + this->z * p_other.z);
}

Vec4 Vec4::operator*(const float p_scale) const
{
	return Vec4(p_scale * this->x, p_scale * this->y, p_scale * this->z, this->w * p_scale);
}

Vec4& Vec4::operator=(const Vec4 & p_other) = default;

Vec4& Vec4::operator/=(const float p_scale)
{
	x /= p_scale;
	y /= p_scale;
	z /= p_scale;
	w /= p_scale;
	return *this;
}
#pragma endregion

void Vec4::Homogenize()
{
	if (this->w != 0)
	{
		this->x = this->x / this->w;
		this->y = this->y / this->w;
		this->z = this->z / this->w;
	}
}

float Vec4::Getmagnitude() const
{
	return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

void Vec4::Normalize()
{
	this->x /= this->Getmagnitude();
	this->y /= this->Getmagnitude();
	this->z /= this->Getmagnitude();
}

Vec4 Vec4::Cross(const Vec4 & p_other) const
{
	return Vec4(this->y * p_other.z - this->z * p_other.y, this->z * p_other.x - this->x * p_other.z, this->x * p_other.y - this->y * p_other.x, this->w);
}