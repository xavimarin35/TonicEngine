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

bool CanvasUI::Update()
{
	/*for (std::list<GameObject*>::iterator it = canvas_elements.begin(); it != canvas_elements.end(); it++)
	{
		(*it)->Update();
	}*/

	return true;
}
