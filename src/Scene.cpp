#include "Scene.h"
#include "GraphParser.h"

using namespace Gyvr::Object;

Scene::Scene(Gyvr::Util::SharedContext& p_sharedContext)
	: m_sharedContext(p_sharedContext), m_root(std::make_shared<Object::GameObject>(m_sharedContext))
{
	SetName("Scene");
}

Gyvr::Object::GameObject& Scene::GetRoot() const
{
	return *m_root;
}