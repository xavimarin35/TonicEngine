#include "GameObject.h"
#include "ModuleGUI.h"
#include "Component.h"

GameObject::GameObject(std::string name)
{
	this->oData.GOname = name;
	this->oData.active = true;
	CreateComponent(COMPONENT_TYPE::TRANSFORM);
	CreateComponent(COMPONENT_TYPE::MESH);
	CreateComponent(COMPONENT_TYPE::TEXTURE);
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

void GameObject::Draw()
{
	for (int i = 0; i < componentsList.size(); ++i)
	{
		componentsList[i]->Draw();
	}
}

void GameObject::EnableGameObject()
{
	if (oData.active)
		oData.active = true;
}

void GameObject::DisableGameObject()
{
	if (oData.active)
		oData.active = false;
}

Component* GameObject::CreateComponent(COMPONENT_TYPE type, bool active)
{
	Component* component = nullptr;

	switch (type) 
	{
	case COMPONENT_TYPE::TRANSFORM:
		component = new ComponentTransform(this);
		LOG_IMGUI_CONSOLE("Component transform added to the list");
		break;
	case COMPONENT_TYPE::MESH:
		component = new ComponentMesh(this);
		LOG_IMGUI_CONSOLE("Component mesh added to the list");
		break;
	case COMPONENT_TYPE::TEXTURE:
		component = new ComponentTexture(this);
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

ComponentTransform* GameObject::GetComponentTransform()
{
	Component* transform = nullptr;
	for (std::vector<Component*>::iterator i = componentsList.begin(); i != componentsList.end(); i++)
	{
		if ((*i)->type == COMPONENT_TYPE::TRANSFORM)
		{
			return (ComponentTransform*)*i;
		}
	}
	return (ComponentTransform*)transform;
}

ComponentMesh* GameObject::GetComponentMesh()
{
	Component* mesh = nullptr;
	for (std::vector<Component*>::iterator i = componentsList.begin(); i != componentsList.end(); i++)
	{
		if ((*i)->type == COMPONENT_TYPE::MESH)
		{
			return (ComponentMesh*)*i;
		}
	}
	return (ComponentMesh*)mesh;
}

ComponentTexture* GameObject::GetComponentTexture()
{
	Component* texture = nullptr;
	for (std::vector<Component*>::iterator i = componentsList.begin(); i != componentsList.end(); i++)
	{
		if ((*i)->type == COMPONENT_TYPE::TEXTURE)
		{
			return (ComponentTexture*)*i;
		}
	}
	return (ComponentTexture*)texture;
}

void GameObject::AssignNameToGO(const char* name)
{
	this->oData.GOname = name;
}

