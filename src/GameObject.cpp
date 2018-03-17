#include "GameObject.h"
#include "MeshRenderer.h"
#include "GraphParser.h"

using namespace Gyvr::Object;

GameObject::GameObject(Gyvr::Util::SharedContext& p_sharedContext, GameObject& p_parent, const std::string& p_name)
	: m_sharedContext(p_sharedContext)
{
	SetName(p_name);

	SetParent(p_parent);
	p_parent.AddChild(*this);

	Setup();
}

GameObject::GameObject(Gyvr::Util::SharedContext& p_sharedContext)
	: m_sharedContext(p_sharedContext)
{
	SetName("Scene Root");

	Setup();

	GetComponent<Transform>()->SetScale(Math::Vec3(10, 15, 20));
}

void Gyvr::Object::GameObject::AddComponent(const std::string & p_type)
{
	if (p_type == "Transform") AddComponent<Transform>();
	else if (p_type == "Light") AddComponent<Light>();
	else if (p_type == "Camera") AddComponent<Camera>();
	else if (p_type == "MeshRenderer") AddComponent<MeshRenderer>();
	else
	{
		Gyvr::Core::Debug::Log::Process("Couldn't add component \"" + p_type + "\" because it doesn't exists in GyvrEngine", Gyvr::Core::Debug::Log::LogLevel::LOG_ERROR);
	}
}

void GameObject::AddChild(GameObject& p_child)
{
	m_childs.push_back(std::shared_ptr<GameObject>(&p_child));
}

std::unordered_map<const std::type_info*, std::shared_ptr<AComponent>>& Gyvr::Object::GameObject::GetComponents()
{
	return m_components;
}

std::vector<std::shared_ptr<GameObject>>& GameObject::GetChilds()
{
	return m_childs;
}

GameObject& GameObject::GetParent() const
{
	return *m_parent;
}

bool Gyvr::Object::GameObject::HasParent() const
{
	return m_parent;
}

void GameObject::Setup()
{
	AddComponent<Transform>();
}

void GameObject::Draw()
{
	auto meshRenderer = GetComponent<MeshRenderer>();

	if (meshRenderer)
		meshRenderer->Draw();
}

void Gyvr::Object::GameObject::Update()
{
	auto camera = GetComponent<Camera>();

	if (camera)
		camera->Update();
}

void GameObject::SetParent(GameObject& p_parent)
{
	m_parent = &p_parent;
}
