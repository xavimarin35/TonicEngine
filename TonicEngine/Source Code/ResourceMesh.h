#ifndef __ResourceMesh_H__
#define __ResourceMesh_H__

#include "Resource.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"

struct mesh_data
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
	float3* face_normals = nullptr;

	// face with 3 indices
	bool indices3 = true;
};

class ResourceMesh : public Resource
{
public:

	ResourceMesh(uint uuid) : Resource(uuid, RESOURCE_TYPE::MESH) {}
	virtual ~ResourceMesh() {}

	bool LoadInMemory();
	void ReleaseMemory();

	mesh_data data;
};

#endif