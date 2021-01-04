#ifndef _COMPONENT_CONTAINER_H_
#define _COMPONENT_CONTAINER_H_

#include "Component.h"
#include "ComponentTransform.h"
#include "SDL/include/SDL_rect.h"

class ElementUI;
class ContainerUI;
class ResourceMesh;
class ComponentTransform;

struct AnchorPoints 
{
	float min_x, min_y, max_x, max_y;
};

class ComponentContainer : public Component
{
public:

	ComponentContainer(GameObject* parent);
	~ComponentContainer();

	bool Start();
	bool Update();
	bool CleanUp();
	void Draw();
	void DrawInspector();
	void DrawAnchorPoint(float3 pos, float2 length);

	// Functions

	void Rect2ScreenSize();
	void CreateQuad();
	void DrawFrame();
	//void DebugDrawSize();
	void Resize(float2 size);

	float2 GetRelativePos() const;
	void SetRelativePos(float2 newPos);

	void UpdateRectAnchors();

	ComponentTransform* GetTransform();
	AnchorPoints GetAnchorPoint() const;
	void SetAnchorPoint(float minX, float minY, float maxX, float maxY);

	float width, height;
	float3 scale;

private:

	ResourceMesh* mesh;
	ComponentTransform* transf;

	AnchorPoints anchor;

	float2 relative_pos;

	ContainerUI* parent;
};

#endif