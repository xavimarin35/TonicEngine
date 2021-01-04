#include "ContainerUI.h"
#include "ResourceMesh.h"
#include "Application.h"

ContainerUI::ContainerUI(ImVec2 size)
{
	quad_mesh = nullptr;
	CreateElementContainer(size);
}

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

void ContainerUI::CreateElementContainer(ImVec2 size)
{
	quad_mesh = new ResourceMesh(App->GenerateUUID());
	quad_mesh->LoadInMemory();
}

void ContainerUI::InvertImage(ImVec2 size)
{
	quad_mesh->CleanData();
	quad_mesh->SetVertexData(size);

	quad_mesh->data.tex_coords[0] = 0.0f;
	quad_mesh->data.tex_coords[1] = 0.0f;
	quad_mesh->data.tex_coords[2] = 0.0f;

	quad_mesh->data.tex_coords[3] = 1.0f;
	quad_mesh->data.tex_coords[4] = 0.0f;
	quad_mesh->data.tex_coords[5] = 0.0f;

	quad_mesh->data.tex_coords[6] = 0.0f;
	quad_mesh->data.tex_coords[7] = 1.0f;
	quad_mesh->data.tex_coords[8] = 0.0f;

	quad_mesh->data.tex_coords[9] = 1.0f;
	quad_mesh->data.tex_coords[10] = 1.0f;
	quad_mesh->data.tex_coords[11] = 0.0f;

	quad_mesh->LoadInMemory();
}

void ContainerUI::ResizeContainer(float x, float y)
{
	CreateElementContainer({ x,y });
}

ResourceMesh* ContainerUI::GetMesh() const
{
	return quad_mesh;
}

void ContainerUI::SetMesh(ResourceMesh* newMesh)
{
	quad_mesh = newMesh;
}