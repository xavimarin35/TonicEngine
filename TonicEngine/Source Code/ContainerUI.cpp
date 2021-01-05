#include "ContainerUI.h"
#include "ResourceMesh.h"
#include "ModuleResources.h"

ContainerUI::ContainerUI()
{
	container_mesh = nullptr;
	CreateContainerRect();
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
	CreateContainerRect();
	SetUpContainerRect(container_mesh, { 10, 10 });
	DrawContainerRect(container_mesh, White);

	return true;
}

void ContainerUI::ResizeContainer(float x, float y)
{
	if (container_mesh != nullptr)
		ResetContainerRect(container_mesh);

	CreateContainerRect({ x, y });
}

ResourceMesh* ContainerUI::GetContainerMesh()
{
	return container_mesh;
}

void ContainerUI::CreateContainerRect(float2 size)
{
	container_mesh = new ResourceMesh(App->GenerateUUID());
	container_mesh->LoadInMemory();
}

void ContainerUI::SetUpContainerRect(ResourceMesh* mesh, float2 size)
{
	uint canvas_numvertex = mesh->data.num_vertex = 4;

	mesh->data.vertex = new float3[canvas_numvertex];

	float2 half_size = (float2)size / 2.0f;

	mesh->data.vertex[0] = { -half_size.x, half_size.y, 0 };
	mesh->data.vertex[1] = { half_size.x, half_size.y, 0 };
	mesh->data.vertex[2] = { -half_size.x, -half_size.y, 0 };
	mesh->data.vertex[3] = { half_size.x, -half_size.y, 0 };

	uint canvas_numindex = mesh->data.num_index = 6;
	mesh->data.index = new uint[canvas_numindex];

	//Front
	mesh->data.index[0] = 0;
	mesh->data.index[1] = 2;
	mesh->data.index[2] = 1;

	mesh->data.index[3] = 1;
	mesh->data.index[4] = 2;
	mesh->data.index[5] = 3;

	uint canvas_numuvs = mesh->data.num_tex_coords = canvas_numvertex;
	mesh->data.tex_coords = new float[canvas_numuvs * 3];

	//Front 
	mesh->data.tex_coords[0] = 0.0f;
	mesh->data.tex_coords[1] = 1.0f;
	mesh->data.tex_coords[2] = 0.0f;

	mesh->data.tex_coords[3] = 1.0f;
	mesh->data.tex_coords[4] = 1.0f;
	mesh->data.tex_coords[5] = 0.0f;

	mesh->data.tex_coords[6] = 0.0f;
	mesh->data.tex_coords[7] = 0.0f;
	mesh->data.tex_coords[8] = 0.0f;

	mesh->data.tex_coords[9] = 1.0f;
	mesh->data.tex_coords[10] = 0.0f;
	mesh->data.tex_coords[11] = 0.0f;
}

void ContainerUI::DrawContainerRect(ResourceMesh* mesh, Color color)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.5f);
	glDisable(GL_CULL_FACE);

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_QUADS);

	glVertex3fv((GLfloat*)&mesh->data.vertex[2]);
	glVertex3fv((GLfloat*)&mesh->data.vertex[3]);
	glVertex3fv((GLfloat*)&mesh->data.vertex[1]);
	glVertex3fv((GLfloat*)&mesh->data.vertex[0]);

	glEnd();
	glLineWidth(1.0f);
	glColor3f(255, 255, 255);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ContainerUI::ResetContainerRect(ResourceMesh* mesh)
{
	if (mesh->data.id_vertex != 0)
	{
		glDeleteBuffers(1, &mesh->data.id_vertex);
		mesh->data.id_vertex = 0;
	}

	if (mesh->data.id_index != 0)
	{
		glDeleteBuffers(1, &mesh->data.id_index);
		mesh->data.id_index = 0;
	}
}
