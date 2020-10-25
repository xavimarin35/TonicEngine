#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Application.h"
#include "Component.h"

class ComponentTransform;
class ComponentMesh;
class ComponentTexture;

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

public:
	bool active = true;
	std::vector<Component*> componentsList;

	ComponentTransform* cTransform = nullptr;
	ComponentMesh* cMesh = nullptr;
	ComponentTexture* cTexture = nullptr;

};



#endif
