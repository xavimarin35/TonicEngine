#ifndef __UI_CANVAS_H__
#define __UI_CANVAS_H__

#include "GameObject.h"
#include <list>

class ComponentCanvas;

class CanvasUI
{
public:
	CanvasUI(ComponentCanvas* canvas);
	~CanvasUI();

	ComponentCanvas* Ccanvas;

	void Update();

	std::list<GameObject*> canvas_elements;
};

#endif
