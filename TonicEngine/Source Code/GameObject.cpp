#include "GameObject.h"
#include "ModuleGUI.h"
#include "Component.h"
#include "ModuleSceneIntro.h"
#include "imgui-1.78/ImGuizmo.h"
#include "ModuleCamera3D.h"
#include "Color.h"

GameObject::GameObject(std::string name)
{
	this->data.name = name;
	this->data.UUID = GenerateUUID();
	CreateComponent(COMPONENT_TYPE::TRANSFORM);

	LOG_C("A new GameObject called '%s' has been created!", name.c_str());
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	for (std::vector<GameObject*>::iterator it = childrenList.begin(); it != childrenList.end(); ++it)
	{
		(*it)->Update();
	}

	if (this->data.active)
	{
		if (this->GetComponentTransform()->moved)
			TransformGlobal(this);

		UpdateBoundingBox();

		if (App->gui->Pstate->drawOwnBB && App->scene_intro->GOselected != nullptr && App->scene_intro->GOselected->data.active)
			DrawOwnBoundingBox(App->scene_intro->GOselected);

		if (App->gui->Pconfig->drawBB)
		{
			App->gui->Pstate->drawOwnBB = false;
			DrawAllBoundingBoxes();
		}
	}
}

void GameObject::CleanUp()
{

	// Deleting Components
	for (int i = 0; i < componentsList.size(); ++i)
	{
		if (componentsList[i] != nullptr && componentsList[i]->active)
			componentsList[i]->CleanUp();

		delete componentsList[i];
		componentsList[i] = nullptr;
	}

	componentsList.clear();

	// Deleting GOs
	if (GOparent != nullptr)
	{
		GOparent->RemoveChild(this);
	}

	for (uint i = 0; i < childrenList.size(); ++i)
	{
		if (childrenList[i] != nullptr)
		{
			childrenList[i]->CleanUp();
		}
	}

	childrenList.clear();
}

void GameObject::EnableGameObject()
{
	if (!this->data.active)
		this->data.active = true;

	for (std::vector<GameObject*>::iterator it = childrenList.begin(); it != childrenList.end(); ++it)
	{
		(*it)->EnableGameObject();
	}

}

void GameObject::DisableGameObject()
{
	if (this->data.active)
		this->data.active = false;

	for (std::vector<GameObject*>::iterator it = childrenList.begin(); it != childrenList.end(); ++it)
	{
		(*it)->DisableGameObject();
	}

}

Component* GameObject::CreateComponent(COMPONENT_TYPE type, bool active)
{
	Component* component = nullptr;

	switch (type) 
	{
	case COMPONENT_TYPE::TRANSFORM:
		component = new ComponentTransform(this);
		break;
	case COMPONENT_TYPE::MESH:
		component = new ComponentMesh(this);
		break;
	case COMPONENT_TYPE::TEXTURE:
		component = new ComponentTexture(this);
		break;
	case COMPONENT_TYPE::CAMERA:
		component = new ComponentCamera(this);
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

ComponentCamera* GameObject::GetComponentCamera()
{
	Component* camera = nullptr;
	for (std::vector<Component*>::iterator i = componentsList.begin(); i != componentsList.end(); i++)
	{
		if ((*i)->type == COMPONENT_TYPE::CAMERA)
		{
			return (ComponentCamera*)*i;
		}
	}
	return (ComponentCamera*)camera;
}

bool GameObject::IsGameObjectActive()
{
	return data.active;
}

const char* GameObject::GetGameObjectName()
{
	return data.name.c_str();
}

uint GameObject::GetGameObjectId()
{
	return data.id;
}

int GameObject::GetGameObjectUUID()
{
	return data.UUID;
}

GameObject* GameObject::GetRootGameObject()
{
	return App->scene_intro->GOroot;
}

void GameObject::AddChild(GameObject* child)
{
	if (child->GOparent != nullptr)
		child->GOparent->RemoveChild(child);

	child->GOparent = this;
	childrenList.push_back(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	for (int i = 0; i < childrenList.size(); i++)
	{
		if (childrenList[i] == child)
		{
			childrenList.erase(childrenList.begin() + i);
		}
	}
}

void GameObject::TransformGlobal(GameObject* GO)
{
	ComponentTransform* transform = GO->GetComponentTransform();
	transform->TransformGlobalMat(GO->GOparent->GetComponentTransform()->GetGlobalTransform());

	for (std::vector<GameObject*>::iterator it = GO->childrenList.begin(); it != GO->childrenList.end(); ++it)
	{
		TransformGlobal(*it);
	}
}

int GameObject::GenerateUUID()
{
	int uuid = GenerateRandomBetween(99999999999);
	return uuid;
}

void GameObject::Save(uint obj_num, nlohmann::json& scene)
{
	scene["Game Objects"][obj_num]["Name"] = data.name;
	scene["Game Objects"][obj_num]["Id"] = data.id;
	scene["Game Objects"][obj_num]["UUID"] = data.UUID;
	scene["Game Objects"][obj_num]["Active"] = data.active;
	
	for (int i = 0; i < componentsList.size(); i++)
		componentsList[i]->Save(obj_num, scene);
}

void GameObject::UpdateBoundingBox()
{
	ComponentMesh* mesh = this->GetComponentMesh();

	if (mesh)
	{
		obb = mesh->BoundingBox();
		obb.Transform(this->GetComponentTransform()->GetGlobalTransform());

		aabb.SetNegativeInfinity();
		aabb.Enclose(obb);
	}
}

void GameObject::DrawAllBoundingBoxes()
{
	glBegin(GL_LINES);
	glLineWidth(App->scene_intro->bbSize);

	glColor4f(App->scene_intro->bbColor.r, App->scene_intro->bbColor.g, App->scene_intro->bbColor.b, App->scene_intro->bbColor.a);

	for (uint i = 0; i < 12; i++)
	{
		glVertex3f(aabb.Edge(i).a.x, aabb.Edge(i).a.y, aabb.Edge(i).a.z);
		glVertex3f(aabb.Edge(i).b.x, aabb.Edge(i).b.y, aabb.Edge(i).b.z);
	}

	glColor3ub(255, 255, 255);

	glEnd();
}

bool GameObject::DrawOwnBoundingBox(GameObject* GO)
{
	bool ret = true;

	if (GO == nullptr)
		return false;
	
	if (GO != nullptr)
	{
		ComponentMesh* m = GO->GetComponentMesh();

		if (m)
		{
			obb = m->BoundingBox();

			obb.Transform(GO->GetComponentTransform()->GetGlobalTransform());

			aabb.SetNegativeInfinity();
			aabb.Enclose(obb);
		}

		glBegin(GL_LINES);
		glLineWidth(0.5f);

		glColor4f(App->scene_intro->bbColor.r, App->scene_intro->bbColor.g, App->scene_intro->bbColor.b, App->scene_intro->bbColor.a);

		for (uint i = 0; i < 12; i++)
		{
			glVertex3f(aabb.Edge(i).a.x, aabb.Edge(i).a.y, aabb.Edge(i).a.z);
			glVertex3f(aabb.Edge(i).b.x, aabb.Edge(i).b.y, aabb.Edge(i).b.z);
		}

		glColor3ub(255, 255, 255);

		glEnd();
	}

	return ret;
}

void GO::FillChildren(std::vector<const GameObject*>& array_, const GameObject* GO, bool parent, uint c)
{
	if (c != 0) array_.push_back(GO);
	else if (parent) array_.push_back(GO);

	c++;

	if (GO->childrenList.size() > 0)
	{
		for (int i = 0; i < GO->childrenList.size(); ++i)
		{
			FillChildren(array_, GO->childrenList[i], parent, c);
		}
	}
}