#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Application.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"

class ComponentTransform;
class ComponentMesh;
class ComponentTexture;

enum class SHAPE_TYPE {
	NONE = -1, 
	CUBE
};

struct objData {
	uint id;
	string name;
	bool active = true;
};

class GameObject
{
public:
	GameObject(string name);
	virtual ~GameObject();

	void Update();
	void CleanUp();

	void EnableGameObject();
	void DisableGameObject();

	Component* ComponentFactory(COMPONENT_TYPE type, bool active = true);
	Component* GetComponent(COMPONENT_TYPE& type);


public:
	objData data;

	std::vector<Component*> componentsList;

	ComponentTransform* cTransform = nullptr;
	ComponentMesh* cMesh = nullptr;
	ComponentTexture* cTexture = nullptr;

};



#endif
