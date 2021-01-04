#include "ComponentContainer.h"

ComponentContainer::ComponentContainer(GameObject* parent) : Component(COMPONENT_TYPE::CONTAINER_UI, parent)
{
	type = COMPONENT_TYPE::CONTAINER_UI;
}

ComponentContainer::~ComponentContainer()
{
}

bool ComponentContainer::Start()
{
	return false;
}

bool ComponentContainer::Update()
{
	return false;
}

bool ComponentContainer::CleanUp()
{
	return false;
}

void ComponentContainer::Draw()
{
}

void ComponentContainer::DrawInspector()
{
}
