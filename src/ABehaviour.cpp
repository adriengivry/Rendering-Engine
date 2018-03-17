#include "ABehaviour.h"

using namespace Gyvr::Object;

ABehaviour::ABehaviour()
{
	SetName("ABehaviour");
	SetActive(true);
}

bool ABehaviour::IsActive() const
{
	return m_active;
}

void ABehaviour::SetActive(bool p_state)
{
	m_active = p_state;
}
