#ifndef _CONTAINER_UI_H_
#define _CONTAINER_UI_H_

#include "ElementUI.h"
#include "imgui-1.78/imgui.h"
#include "Color.h"
#include "Math.h"

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

	void ResizeContainer(float x, float y);
	ResourceMesh* GetContainerMesh();

	void CreateContainerRect(float2 size = { 1, 1 });
	void SetUpContainerRect(ResourceMesh* mesh, float2 size = { 1, 1 });
	void DrawContainerRect(ResourceMesh* mesh, Color color);
	void ResetContainerRect(ResourceMesh* mesh);

	ResourceMesh* container_mesh = nullptr;

private:


};

#endif
