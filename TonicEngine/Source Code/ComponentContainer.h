#ifndef _COMPONENT_CONTAINER_H_
#define _COMPONENT_CONTAINER_H_

#include "Component.h"

class ElementUI;
class ContainerUI;

class ComponentContainer : public Component
{
public:

	ComponentContainer(GameObject* parent);
	~ComponentContainer();

	bool Start();
	bool Update();
	bool CleanUp();
	void Draw();
	void DrawInspector();

private:

	ContainerUI* container = nullptr;


};

#endif
