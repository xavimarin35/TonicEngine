#include "CanvasUI.h"
#include "ComponentCanvas.h"
#include "ModuleGUI.h"

CanvasUI::CanvasUI(ComponentCanvas* canvas)
{
	Ccanvas = canvas;
}

CanvasUI::~CanvasUI()
{
}

bool CanvasUI::Start()
{
	return true;
}

bool CanvasUI::Update()
{
	for (std::vector<GameObject*>::iterator it = canvas_elements.begin(); it != canvas_elements.end(); it++)
	{
		(*it)->Update();
	}

	return true;
}

void CanvasUI::CreateCanvasRect()
{
	canvas_mesh = new ResourceMesh(App->GenerateUUID());
	canvas_mesh->LoadInMemory();
}

void CanvasUI::SetUpCanvasRect(ResourceMesh* mesh, float2 size)
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

void CanvasUI::DrawCanvasRect(ResourceMesh* mesh, Color color)
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


