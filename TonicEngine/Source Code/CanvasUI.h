#ifndef __CANVAS_UI_H__
#define __CANVAS_UI_H__

#include "GameObject.h"
#include <list>


class CanvasUI
{
public:
	CanvasUI();
	~CanvasUI();

	bool Update();

	std::list<GameObject*> canvas_elements;
};

#endif
