#ifndef __C_MESH_H__
#define __C_MESH_H__

#include "Component.h"
#include "glmath.h"
#include "Color.h"
#include "ResourceMesh.h"

class GameObject;

struct meshData 
{
	uint id_index = 0;
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0;
	uint num_vertex = 0;
	float3* vertex = nullptr;

	uint id_tex_coords = 0;
	uint num_tex_coords = 0;
	float* tex_coords = nullptr;

	uint num_normals = 0;
	float3* face_center = nullptr;
	float3* normals = nullptr;

	string path;

	uint texture = 0;
};

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* gameObject);
	virtual ~ComponentMesh();

	bool Update();
	bool CleanUp();

	void Draw() override;

	void DrawInspector();
	bool DrawFaceNormals(GameObject* m, bool active = false);
	bool DrawVertexNormals(GameObject* m, bool active = false);
	void IsMeshComponentActive(GameObject* go);

	const AABB& BoundingBox();

	void Save(uint obj_num, nlohmann::json& scene_file);

public:

	bool showFaceNormals = false;
	bool showVertexNormals = false;

	float faceLenght = 1.0f;
	Color faceColor = Red;

	float vertexLenght = 1.0f;
	Color vertexColor = Blue;
	
	meshData mData;

	AABB aabb;

	ResourceMesh* rMesh = nullptr;

};

#endif
