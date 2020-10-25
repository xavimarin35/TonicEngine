#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Application.h"

class GameObject;

enum class COMPONENT_TYPE
{
	NONE = -1,
	TRANSFORM,
	MESH,
	TEXTURE
};

class Component
{
public:
	Component(COMPONENT_TYPE type, GameObject* GO, bool active = true);
	virtual ~Component();

	virtual bool Update();
	virtual bool CleanUp();

	virtual void EnableComponent();
	virtual void DisableComponent();

public:
	bool active = true;
	COMPONENT_TYPE type;
	GameObject* gameobject;
};





#endif
