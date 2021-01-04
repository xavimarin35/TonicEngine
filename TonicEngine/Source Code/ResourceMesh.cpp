#include "ResourceMesh.h"
#include "ModuleResources.h"
#include "MeshImporter.h"

#include "glew/include/GL/glew.h"

bool ResourceMesh::LoadInMemory()
{
	this->references++;
	return App->mesh_imp->Load(this);
}

void ResourceMesh::ReleaseMemory()
{
	std::map<uint, Resource*>::const_iterator it = App->resources->resources.find(this->res_UUID);
	App->resources->resources.erase(it);

	glDeleteBuffers(1, (GLuint*)&data.id_index);
	glDeleteBuffers(1, (GLuint*)&data.id_vertex);
	glDeleteBuffers(1, (GLuint*)&data.id_tex_coords);

	delete this;
}

bool ResourceMesh::SetVertexData(ImVec2 size)
{
	data.num_vertex = 4;
	data.vertex = new float3[data.num_vertex];

	ImVec2 half;
	half.x = size.x / 2.0f;
	half.y = size.y / 2.0f;

	data.vertex[0] = { -half.x, half.y, 0 };
	data.vertex[1] = { half.x, half.y, 0 };
	data.vertex[2] = { -half.x, -half.y, 0 };
	data.vertex[3] = { half.x, -half.y, 0 };

	data.num_index = 6;
	data.index = new uint[data.num_index];

	//Front
	data.index[0] = 0;
	data.index[1] = 2;
	data.index[2] = 1;

	data.index[3] = 1;
	data.index[4] = 2;
	data.index[5] = 3;

	data.num_tex_coords = data.num_vertex;
	data.tex_coords = new float[data.num_tex_coords * 3];

	//Front 
	data.tex_coords[0] = 0.0f;
	data.tex_coords[1] = 1.0f;
	data.tex_coords[2] = 0.0f;

	data.tex_coords[3] = 1.0f;
	data.tex_coords[4] = 1.0f;
	data.tex_coords[5] = 0.0f;

	data.tex_coords[6] = 0.0f;
	data.tex_coords[7] = 0.0f;
	data.tex_coords[8] = 0.0f;

	data.tex_coords[9] = 1.0f;
	data.tex_coords[10] = 0.0f;
	data.tex_coords[11] = 0.0f;

	return true;
}

float3 ResourceMesh::CenterVertices(float3* vertices, int num)
{
	float3 min = float3::inf;
	float3 max = -float3::inf;
	for (int i = 0; i < num; i++)
	{
		if (vertices[i].x > max.x) max.x = vertices[i].x;
		if (vertices[i].y > max.y) max.y = vertices[i].y;
		if (vertices[i].z > max.z) max.z = vertices[i].z;

		if (vertices[i].x < min.x) min.x = vertices[i].x;
		if (vertices[i].y < min.y) min.y = vertices[i].y;
		if (vertices[i].z < min.z) min.z = vertices[i].z;
	}

	for (int i = 0; i < num; i++)
		vertices[i] -= (max + min) / 2;

	return(max + min) / 2;
}

void ResourceMesh::CleanData()
{
	if (references == 0)
	{
		if (data.id_vertex != 0)
		{
			glDeleteBuffers(1, &data.id_vertex);
			data.id_vertex = 0;
		}

		if (data.id_index != 0)
		{
			glDeleteBuffers(1, &data.id_index);
			data.id_index = 0;
		}
	}

	//App->resources->DeleteFromList(uid);

}