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

void CanvasUI::DrawCanvasRect(ResourceMesh* mesh, float3* vert, Color color)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.5f);
	glDisable(GL_CULL_FACE);

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_QUADS);

	/*glVertex3fv((GLfloat*)&vert[2]);	--> This way can be functional
	glVertex3fv((GLfloat*)&vert[3]);
	glVertex3fv((GLfloat*)&vert[1]);
	glVertex3fv((GLfloat*)&vert[0]);

	// ------------ We must use one of these two 

	glVertex3fv((GLfloat*)&mesh->data.vertex[2]);	 --> Or this way can also be functional too
	glVertex3fv((GLfloat*)&mesh->data.vertex[3]);
	glVertex3fv((GLfloat*)&mesh->data.vertex[1]);
	glVertex3fv((GLfloat*)&mesh->data.vertex[0]);*/

	glEnd();
	glLineWidth(1.0f);
	glColor3f(255, 255, 255);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
