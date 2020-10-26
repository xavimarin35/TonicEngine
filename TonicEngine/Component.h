#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Application.h"

class GameObject;

enum class COMPONENT_TYPE
{
	NONE = -1,
	TRANSFORM,
	MESH,
	TEXTURE
};

struct meshData {
	uint id_index = 0;
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0;
	uint num_vertex = 0;
	float3* vertex = nullptr;

	uint id_tex_coords = 0;
	uint num_tex_coords = 0;
	float* tex_coords = nullptr;

	bool draw_normals = false;

	uint texture = 0;
};

class Component
{
public:
	Component(COMPONENT_TYPE type, GameObject* GO, bool active = true);
	virtual ~Component();

	virtual bool Update();
	virtual bool CleanUp();

	virtual void Draw();
	COMPONENT_TYPE GetComponentType() const;
	virtual void EnableComponent();
	virtual void DisableComponent();

public:
	bool active = true;
	COMPONENT_TYPE type = COMPONENT_TYPE::NONE;
	GameObject* object;

	meshData mData;
};





#endif
