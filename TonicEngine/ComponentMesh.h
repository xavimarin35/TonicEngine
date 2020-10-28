#ifndef __C_MESH_H__
#define __C_MESH_H__

#include "Component.h"
#include "glmath.h"

class GameObject;

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

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* gameObject, bool active);
	virtual ~ComponentMesh();

	bool Update();
	void Draw();
	void DrawFaceNormals(GameObject* m);
	void DrawVertexNormals(GameObject* m);

public:

	bool showFaceNormals = false;
	bool showVertexNormals = false;
	
	meshData mData;

};

#endif
