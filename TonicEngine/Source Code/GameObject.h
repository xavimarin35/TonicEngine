#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Application.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentCamera.h"
#include "ModuleInput.h"

class ComponentTransform;
class ComponentMesh;
class ComponentTexture;
class ComponentCamera;

struct objData;
struct meshData;

struct objData {
	uint GOid = -1;
	string GOname;
	bool active = true;
};

class GameObject
{
public:
	GameObject(std::string name);
	virtual ~GameObject();

	void Update();
	void CleanUp();
	void Draw();

	void EnableGameObject();
	void DisableGameObject();

	Component* CreateComponent(COMPONENT_TYPE type, bool active = true);
	Component* GetComponent(const COMPONENT_TYPE& type);

	ComponentTransform* GetComponentTransform();
	ComponentMesh* GetComponentMesh();
	ComponentTexture* GetComponentTexture();
	ComponentCamera* GetComponentCamera();


	void AssignNameToGO(const char* name);
	void AddChild(GameObject* GO);
	void RemoveChild(GameObject* GO);

public:
	objData oData;

	std::vector<Component*> componentsList;

	std::vector<GameObject*> childrenList;
	GameObject* GOparent = nullptr;
	

	uint textureWidth = 1024;
	uint textureHeight = 1024;

};

#endif
