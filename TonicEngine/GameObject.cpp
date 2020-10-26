#include "GameObject.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"

GameObject::GameObject(string name)
{
	this->data.name = name;
	this->data.active = true;
	cTransform = (ComponentTransform*)ComponentFactory(COMPONENT_TYPE::TRANSFORM, true);
	cMesh = (ComponentMesh*)ComponentFactory(COMPONENT_TYPE::MESH, true);
	cTexture = (ComponentTexture*)ComponentFactory(COMPONENT_TYPE::TEXTURE, true);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::CleanUp()
{
}

void GameObject::EnableGameObject()
{
	if (data.active)
		data.active = true;
}

void GameObject::DisableGameObject()
{
	if (data.active)
		data.active = false;
}

Component* GameObject::ComponentFactory(COMPONENT_TYPE type, bool active)
{
	Component* component = nullptr;

	switch (type) 
	{
	case COMPONENT_TYPE::TRANSFORM:
		component = new ComponentTransform(this, true);
		break;
	case COMPONENT_TYPE::MESH:
		component = new ComponentMesh(this, true);
		break;
	case COMPONENT_TYPE::TEXTURE:
		component = new ComponentTexture(this, true);
		break;
	}

	if (component != nullptr)
		componentsList.push_back(component);

	return component;
}

Component* GameObject::GetComponent(COMPONENT_TYPE& type)
{
	for (std::vector<Component*>::iterator it = componentsList.begin(); it != componentsList.end(); ++it)
	{
		if (*it != nullptr && (*it)->GetComponentType() == type)
			return *it;
	}
	return nullptr;
}
