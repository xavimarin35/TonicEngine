#include "ComponentCanvas.h"
#include "CanvasUI.h"

ComponentCanvas::ComponentCanvas(GameObject* parent) : Component(COMPONENT_TYPE::CANVAS_UI, parent)
{
	type = COMPONENT_TYPE::CANVAS_UI;
}

ComponentCanvas::~ComponentCanvas()
{
}

bool ComponentCanvas::Start()
{
	canvas = new CanvasUI(this);

	return true;
}

bool ComponentCanvas::Update()
{
	canvas->Update();
	return true;
}

bool ComponentCanvas::CleanUp()
{
	return true;
}

void ComponentCanvas::Draw()
{
	if (!render_elements)
		return;

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (std::list<GameObject*>::iterator it = canvas->canvas_elements.begin(); it != canvas->canvas_elements.end(); it++)
	{
		(*it)->Draw();
	}
}

