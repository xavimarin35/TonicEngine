#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Application.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ModuleInput.h"

class ComponentTransform;
class ComponentMesh;
class ComponentTexture;

struct objData;
struct meshData;

struct objData {
	uint GOid = 0;
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

public:
	objData oData;

	std::vector<Component*> componentsList;

	void AssignNameToGO(const char* name);

	uint textureWidth = 1024;
	uint textureHeight = 1024;

};

#endif
