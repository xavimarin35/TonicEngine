#include "Component.h"

Component::Component(COMPONENT_TYPE type, GameObject* GO, bool active)
{
	this->type = type;
	this->object = GO;
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

void Component::Draw()
{
}

void Component::DrawInspector()
{
}

COMPONENT_TYPE Component::GetComponentType() const
{
	return type;
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