#include "Transform.h"

using namespace Gyvr::Object;
using namespace Gyvr::Math;

Transform::Transform()
{
	SetName("Transform");

	m_position = Vec3(0, 0, 0);
	m_rotation = Vec3(0, 0, 0);
	m_scale = Vec3(0, 0, 0);
}

Transform::Transform(const Vec3& p_position)
{
	m_position = p_position;
	m_rotation = Vec3(0, 0, 0);
	m_scale = Vec3(0, 0, 0);
}

Transform::Transform(const Vec3& p_position, const Vec3& p_rotation)
{
	m_position = p_position;
	m_rotation = p_rotation;
	m_scale = Vec3(0, 0, 0);
}

Transform::Transform(const Vec3& p_position, const Vec3& p_rotation, const Vec3& p_scale)
{
	m_position = p_position;
	m_rotation = p_rotation;
	m_scale = p_scale;
}

Gyvr::Math::Vec3& Transform::GetPosition()
{
	return m_position;
}

Gyvr::Math::Vec3& Transform::GetRotation()
{
	return m_rotation;
}

Gyvr::Math::Vec3& Transform::GetScale()
{
	return  m_scale;
}

void Transform::SetPosition(const Gyvr::Math::Vec3& p_position)
{
	m_position = p_position;
}

void Transform::SetRotation(const Gyvr::Math::Vec3& p_rotation)
{
	m_rotation = p_rotation;
}

void Transform::SetScale(const Gyvr::Math::Vec3& p_scale)
{
	m_scale = p_scale;
}

void Transform::Translate(const Gyvr::Math::Vec3& p_translate)
{
	m_position += p_translate;
}

void Gyvr::Object::Transform::Rotate(const Gyvr::Math::Vec3 & p_rotate)
{
	m_rotation += p_rotate;
}

void Gyvr::Object::Transform::Scale(const Gyvr::Math::Vec3 & p_scale)
{
	m_scale += p_scale;
}
