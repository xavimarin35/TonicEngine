#include "ContainerUI.h"
#include "ResourceMesh.h"
#include "ModuleResources.h"

ContainerUI::ContainerUI()
{
	CreateElementContainer();
}

ContainerUI::~ContainerUI()
{
}

bool ContainerUI::Start()
{
	return true;
}

bool ContainerUI::Update()
{
	return true;
}

bool ContainerUI::CleanUp()
{
	return true;
}

bool ContainerUI::Draw()
{
	return true;
}

bool ContainerUI::CreateElementContainer(ImVec2 size)
{
	container_mesh = (ResourceMesh*)App->resources->CreateResource(RESOURCE_TYPE::MESH); 

	return true;
}
