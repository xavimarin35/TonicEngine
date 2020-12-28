#include "CanvasUI.h"
#include "ComponentCanvas.h"

CanvasUI::CanvasUI(ComponentCanvas* canvas)
{
	Ccanvas = canvas;
}

CanvasUI::~CanvasUI()
{
}

void CanvasUI::Update()
{
	for (std::list<GameObject*>::iterator it = canvas_elements.begin(); it != canvas_elements.end(); it++)
	{
		(*it)->Update();
	}
}
