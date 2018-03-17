#include "AComponent.h"

#include "GameObject.h"

using namespace Gyvr::Object;

AComponent::AComponent()
{
	SetName("AComponent");
}

void AComponent::SetOwner(GameObject& p_owner)
{
	m_owner = &p_owner;
}

GameObject& AComponent::GetOwner() const
{
	return *m_owner;
}
