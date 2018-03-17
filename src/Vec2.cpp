#include "Vec2.h"

#include "MathShared.h"

using namespace Gyvr::Math;

#pragma region Constructors & Destructor
Vec2::Vec2(const float p_x, const float p_y)
{
	this->x = p_x;
	this->y = p_y;
}

Vec2::Vec2(const Vec2 & p_other)
{
	this->x = p_other.x;
	this->y = p_other.y;
}
#pragma endregion

#pragma region Overload
Vec2 Vec2::operator+(const Vec2 & p_other) const
{
	return Vec2(this->x + p_other.x, this->y + p_other.y);
}

Vec2 Vec2::operator-(const Vec2 & p_other) const
{
	return Vec2(this->x - p_other.x, this->y - p_other.y);
}

Vec2 Vec2::operator*(const float p_scale) const
{
	return Vec2(this->x * p_scale, this->y * p_scale);
}

float Vec2::operator*(const Vec2 & p_other) const
{
	return (this->x * p_other.x + this->y * p_other.y);
}
#pragma endregion

float Vec2::Cross(const Vec2& p_other) const
{
	return (this->x * p_other.y - this->y * p_other.x);
}

float Vec2::GetMagnitude() const
{
	return sqrtf((this->x * this->x) + (this->y* this->y));
}

void Vec2::Normalize()
{
	this->x = this->x / this->GetMagnitude();
	this->y = this->y / this->GetMagnitude();
}