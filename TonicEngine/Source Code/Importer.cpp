#include "Application.h"
#include "Importer.h"
#include "ModuleFileSystem.h"

#include "mmgr/mmgr.h"

Importer::Importer()
{
}

Importer::~Importer()
{
}

bool Importer::Import(const char* path, std::string& file, ComponentMesh* mesh)
{
	bool ret = false;

	// Here we see the amount of indices, vertices, etc
	uint range[4] =
	{
		mesh->mData.num_index,
		mesh->mData.num_vertex,
		mesh->mData.num_normals,
		mesh->mData.num_tex_coords
	};

	uint size = 
		sizeof(range) 
		+ sizeof(uint) * mesh->mData.num_index 
		+ sizeof(float) * mesh->mData.num_vertex * 3 
		+ sizeof(float) * mesh->mData.num_normals * 3 * 2 
		+ sizeof(float) * mesh->mData.num_tex_coords * 2;

	// Allocate
	char* data = new char[size];
	char* iterator = data;

	// Storing range
	uint bytes = sizeof(range);
	memcpy(iterator, range, bytes);

	// Storing indices
	iterator += bytes;
	bytes = sizeof(uint) * mesh->mData.num_index;
	memcpy(iterator, mesh->mData.index,bytes);

	// Storing vertices
	iterator +=bytes;
	bytes = sizeof(float) * mesh->mData.num_vertex;
	memcpy(iterator, mesh->mData.vertex, bytes);

	// Storing Normals
	iterator += bytes;
	bytes = sizeof(float) * mesh->mData.num_normals * 3;
	memcpy(iterator, mesh->mData.face_center, bytes);

	iterator += bytes;
	bytes = sizeof(float) * mesh->mData.num_normals * 3;
	memcpy(iterator, mesh->mData.normals, bytes);

	// Storing Texture
	iterator += bytes;
	bytes = sizeof(float) * mesh->mData.num_tex_coords * 2;
	memcpy(iterator, mesh->mData.tex_coords, bytes);

	ret = App->file_system->SaveUnique(file, data, size, LIBRARY_MESH_FOLDER, path, "fbx");

	return ret;
}