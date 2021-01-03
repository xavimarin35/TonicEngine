#ifndef __CANVAS_UI_H__
#define __CANVAS_UI_H__

#include "GameObject.h"
#include <list>

class ComponentCanvas;
class ResourceMesh;

class CanvasUI
{
public:
	CanvasUI(ComponentCanvas* canvas);
	~CanvasUI();

	ComponentCanvas* Ccanvas = nullptr;
	
	bool Start();
	bool Update();
	void CreateCanvasRect();
	void SetUpCanvasRect(ResourceMesh* mesh, float2 size = { 1,1 });
	void DrawCanvasRect(ResourceMesh* mesh, Color color);
	
	std::vector<GameObject*> canvas_elements;
	ResourceMesh* canvas_mesh = nullptr;
};

#endif
