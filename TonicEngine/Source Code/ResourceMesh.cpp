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