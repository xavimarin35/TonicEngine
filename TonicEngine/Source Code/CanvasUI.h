#ifndef __CANVAS_UI_H__
#define __CANVAS_UI_H__

#include "GameObject.h"
#include <list>

class ComponentCanvas;

class CanvasUI
{
public:
	CanvasUI(ComponentCanvas* canvas);
	~CanvasUI();

	ComponentCanvas* Ccanvas = nullptr;

	bool Update();

	std::vector<GameObject*> canvas_elements;
};

#endif
