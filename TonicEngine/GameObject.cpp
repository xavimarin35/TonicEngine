#include "GameObject.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"

GameObject::GameObject(string name)
{
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
	if (active)
		active = true;
}

void GameObject::DisableGameObject()
{
	if (active)
		active = false;
}

Component* GameObject::ComponentFactory(COMPONENT_TYPE type, bool active)
{
	Component* component = nullptr;

	switch (type) 
	{
	case COMPONENT_TYPE::TRANSFORM:
		//component = new ComponentTransform(this);
		break;
	case COMPONENT_TYPE::MESH:
		//component = new ComponentMesh(this);
		break;
	case COMPONENT_TYPE::TEXTURE:
		//component = new ComponentTexture(this);
		break;
	}

	if (component != nullptr)
		componentsList.push_back(component);

	return component;
}
