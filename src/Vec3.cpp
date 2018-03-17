#include "Vec3.h"

#include "MathShared.h"

using namespace Gyvr::Math;

#pragma region Constructors & Destructor
Vec3::Vec3(const float p_x, const float p_y, const float p_z)
{
	this->x = p_x;
	this->y = p_y;
	this->z = p_z;
}

Vec3::Vec3(const Vec3 & p_other)
{
	this->x = p_other.x;
	this->y = p_other.y;
	this->z = p_other.z;
}
#pragma endregion

#pragma region Overload
Vec3 Vec3::operator+(const Vec3& p_other) const
{
	return Vec3(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z);
}

Vec3 Vec3::operator-(const Vec3 & p_other) const
{
	return Vec3(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z);
}

Vec3 Vec3::operator*(const float p_scale) const
{
	return Vec3(p_scale * this->x, p_scale * this->y, p_scale * this->z);
}

Vec3 Vec3::operator/(const float p_scale) const
{
	return Vec3(this->x / p_scale, this->y / p_scale, this->z / p_scale);
}

Vec3& Vec3::operator=(const Vec3 & p_other) = default;

Vec3 & Vec3::operator+=(const Vec3 & p_other)
{
	this->x += p_other.x;
	this->y += p_other.y;
	this->z += p_other.z;
	return *this;
}
#pragma endregion

void Vec3::Normalize()
{
	this->x = this->x / this->GetMagnitude();
	this->y = this->y / this->GetMagnitude();
	this->z = this->z / this->GetMagnitude();
}

float Vec3::dot(const Vec3 & p_other) const
{
	return (x * p_other.x + y * p_other.y + z * p_other.z);
}

Vec3 Vec3::Cross(const Vec3 & p_other) const
{
	return Vec3(this->y * p_other.z - this->z * p_other.y, this->z* p_other.x - this->x * p_other.z, this->x * p_other.y - this->y * p_other.x);
}

float Vec3::GetMagnitude() const
{
	return sqrtf((this->x * this->x) + (this->y* this->y) + (this->z * this->z));
}