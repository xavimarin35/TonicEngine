#ifndef __C_MESH_H__
#define __C_MESH_H__

#include "Component.h"
#include "glmath.h"
#include "Color.h"
#include "ResourceMesh.h"

class GameObject;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* gameObject);
	virtual ~ComponentMesh();

	bool Update();
	bool CleanUp();

	void Draw() override;

	void DrawInspector();

	void IsMeshComponentActive(GameObject* go);

	const AABB& BoundingBox();

	void Save(uint GO_id, nlohmann::json& scene_file);

public:

	bool showFaceNormals = false;
	bool showVertexNormals = false;

	float faceLenght = 1.0f;
	Color faceColor = Red;

	float vertexLenght = 1.0f;
	Color vertexColor = Blue;

	AABB aabb;

	ResourceMesh* rMesh = nullptr;	
};

#endif
