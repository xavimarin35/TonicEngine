#include "Component.h"

Component::Component(COMPONENT_TYPE type, GameObject* GO, bool active)
{
	this->type = type;
	this->gameobject = GO;
	this->active = active;
}

Component::~Component()
{
}

bool Component::Update()
{
	return true;
}

bool Component::CleanUp()
{
	return true;
}

void Component::EnableComponent()
{
	if (active)
		active = true;
}

void Component::DisableComponent()
{
	if (active)
		active = false;
}
