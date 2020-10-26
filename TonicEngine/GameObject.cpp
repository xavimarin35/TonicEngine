#include "GameObject.h"
#include "ModuleGUI.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"

GameObject::GameObject(string name)
{
	this->data.name = name;
	this->data.active = true;
	//ComponentFactory(COMPONENT_TYPE::TRANSFORM, true);
	ComponentFactory(COMPONENT_TYPE::MESH, true);
	//ComponentFactory(COMPONENT_TYPE::TEXTURE, true);
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	for (int i = 0; i < componentsList.size(); ++i)
	{
		if (componentsList[i] != nullptr && componentsList[i]->active)
			componentsList[i]->Update();
	}
}

void GameObject::CleanUp()
{
	for (int i = 0; i < componentsList.size(); ++i)
	{
		if (componentsList[i] != nullptr && componentsList[i]->active)
			componentsList[i]->CleanUp();
	}
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
		LOG_IMGUI_CONSOLE("Component transform added to the list");
		break;
	case COMPONENT_TYPE::MESH:
		component = new ComponentMesh(this, true);
		LOG_IMGUI_CONSOLE("Component mesh added to the list");
		break;
	case COMPONENT_TYPE::TEXTURE:
		component = new ComponentTexture(this, true);
		LOG_IMGUI_CONSOLE("Component texture added to the list");
		break;
	}

	if (component != nullptr) 
	{
		componentsList.push_back(component);
	}
		
	return component;
}

Component* GameObject::GetComponent(const COMPONENT_TYPE& type)
{
	for (std::vector<Component*>::iterator it = componentsList.begin(); it != componentsList.end(); ++it)
	{
		if (*it != nullptr && (*it)->GetComponentType() == type)
		{
			return *it;
		}	
	}
	return nullptr;
}

ComponentTexture* GameObject::GetComponentTransform(COMPONENT_TYPE type)
{
	return nullptr;
}

ComponentMesh* GameObject::GetComponentMesh(COMPONENT_TYPE type)
{
	return nullptr;
}

ComponentTexture* GameObject::GetComponentTexture(COMPONENT_TYPE type)
{
	return nullptr;
}
