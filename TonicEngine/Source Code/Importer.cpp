#include "Application.h"
#include "Importer.h"
#include "ModuleFileSystem.h"
#include "ModuleGUI.h"


//#include "mmgr/mmgr.h"

Importer::Importer()
{
}

Importer::~Importer()
{
}

bool Importer::Export(const char* path, std::string& file, ComponentMesh* mesh)
{
	bool ret = false;

	// Here we see the amount of indices, vertices, etc
	uint range[4] =
	{
		mesh->rMesh->data.num_index,
		mesh->rMesh->data.num_vertex,
		mesh->rMesh->data.num_normals,
		mesh->rMesh->data.num_tex_coords
	};

	uint size = 
		sizeof(range) 
		+ sizeof(uint) * mesh->rMesh->data.num_index
		+ sizeof(float) * mesh->rMesh->data.num_vertex * 3
		+ sizeof(float) * mesh->rMesh->data.num_normals * 3 * 2
		+ sizeof(float) * mesh->rMesh->data.num_tex_coords * 2;

	// Allocate
	char* data = new char[size];
	char* iterator = data;

	// Storing range
	uint bytes = sizeof(range);
	memcpy(iterator, range, bytes);

	// Storing indices
	iterator += bytes;
	bytes = sizeof(uint) * mesh->rMesh->data.num_index;
	memcpy(iterator, mesh->rMesh->data.index,bytes);

	// Storing vertices
	iterator +=bytes;
	bytes = sizeof(float) * mesh->rMesh->data.num_vertex;
	memcpy(iterator, mesh->rMesh->data.vertex, bytes);

	// Storing Normals
	iterator += bytes;
	bytes = sizeof(float) * mesh->rMesh->data.num_normals * 3;
	memcpy(iterator, mesh->rMesh->data.face_center, bytes);

	iterator += bytes;
	bytes = sizeof(float) * mesh->rMesh->data.num_normals * 3;
	memcpy(iterator, mesh->rMesh->data.normals, bytes);

	// Storing Texture
	iterator += bytes;
	bytes = sizeof(float) * mesh->rMesh->data.num_tex_coords * 2;
	memcpy(iterator, mesh->rMesh->data.tex_coords, bytes);

	ret = App->file_system->SaveUnique(file, data, size, LIBRARY_MESH_FOLDER, path, "Tmesh");

	if (ret) 
	{ 
		LOG_C("SUCCESS: Correctly exported %s.Tmesh into Meshes folder", path); 
	}
	else 
	{ 
		LOG_C("ERROR: Failed to export %s.Tmesh into Meshes folder", path); 
	}

	return ret;
}