#include "ComponentContainer.h"
#include "ContainerUI.h"
#include "Color.h"

ComponentContainer::ComponentContainer(GameObject* parent) : Component(COMPONENT_TYPE::CONTAINER_UI, parent)
{
	type = COMPONENT_TYPE::CONTAINER_UI;
}

ComponentContainer::~ComponentContainer()
{
}

bool ComponentContainer::Start()
{
	return true;
}

bool ComponentContainer::Update()
{
	return true;
}

bool ComponentContainer::CleanUp()
{
	return true;
}

void ComponentContainer::Draw()
{
	container->CreateContainerRect();
	container->SetUpContainerRect(container->container_mesh, { 20, 10 });
	container->DrawContainerRect(container->container_mesh, White);
}

void ComponentContainer::DrawInspector()
{
}
