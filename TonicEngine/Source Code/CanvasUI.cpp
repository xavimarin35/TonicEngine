#include "CanvasUI.h"

CanvasUI::CanvasUI() { }

CanvasUI::~CanvasUI() { }

bool CanvasUI::Update()
{
	for (auto it = canvas_elements.begin(); it != canvas_elements.end(); it++)
		(*it)->Update();

	return true;
}