#include "ResourceMesh.h"
#include "ModuleResources.h"
#include "MeshImporter.h"

#include "glew/include/GL/glew.h"

bool ResourceMesh::LoadInMemory()
{
	return App->mesh_imp->Load(this);
}

void ResourceMesh::ReleaseMemory()
{
	std::map<uint, Resource*>::const_iterator it = App->resources->resources.find(this->res_UUID);
	App->resources->resources.erase(it);

	glDeleteBuffers(1, (GLuint*)&data.id_index);
	glDeleteBuffers(1, (GLuint*)&data.id_vertex);
	glDeleteBuffers(1, (GLuint*)&data.id_tex_coords);

	if (data.index != nullptr)
	{
		delete[] data.index;
		data.index = nullptr;
	}

	if (data.vertex != nullptr)
	{
		delete[] data.vertex;
		data.vertex = nullptr;
	}

	if (data.tex_coords != nullptr)
	{
		delete[] data.tex_coords;
		data.tex_coords = nullptr;
	}

	if (data.face_center != nullptr)
	{
		delete[] data.face_center;
		data.face_center = nullptr;
	}

	if (data.face_normal != nullptr)
	{
		delete[] data.face_normal;
		data.face_normal = nullptr;
	}


	delete this;
}
