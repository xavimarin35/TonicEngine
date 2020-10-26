#ifndef __C_MESH_H__
#define __C_MESH_H__

#include "Component.h"
#include "glmath.h"

class GameObject;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* gameObject, bool active);
	virtual ~ComponentMesh();

	void Draw();
	void DrawFaceNormals();
	void DrawVertexNormals();

public:



};

#endif
