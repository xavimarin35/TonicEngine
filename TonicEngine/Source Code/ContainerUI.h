#ifndef _CONTAINER_UI_H_
#define _CONTAINER_UI_H_

#include "ElementUI.h"
#include "imgui-1.78/imgui.h"

class ResourceTexture;
class ResourceMesh;

class ContainerUI : public ElementUI
{
public:
	ContainerUI();
	~ContainerUI();

	bool Start();
	bool Update();
	bool CleanUp();
	bool Draw();

	bool CreateElementContainer(ImVec2 size = { 1,1 }); // Default size --> { 1,1 } 
	void DrawImageUI();

	ResourceTexture* container_tex = nullptr;
	ResourceMesh* container_mesh = nullptr;

private:


};

#endif
