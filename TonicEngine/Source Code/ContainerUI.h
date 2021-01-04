#ifndef _CONTAINER_UI_H_
#define _CONTAINER_UI_H_

#include "ElementUI.h"
#include "imgui-1.78/imgui.h"

class ResourceMesh;

class ContainerUI : public ElementUI
{
public:
	ContainerUI(ImVec2 size);
	ContainerUI();
	~ContainerUI();

	bool Start();
	bool Update();
	bool CleanUp();

	void CreateElementContainer(ImVec2 size = { 1,1 }); // Default size --> { 1,1 } 
	void InvertImage(ImVec2 size = { 1,1 });
	void ResizeContainer(float x, float y);

	ResourceMesh* container_mesh = nullptr;
	ResourceMesh* GetMesh() const;
	void SetMesh(ResourceMesh* mesh);

private:

	ResourceMesh* quad_mesh;


};

#endif
