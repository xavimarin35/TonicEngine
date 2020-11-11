#include "Application.h"
#include "Importer.h"
#include "ModuleFileSystem.h"
#include "ModuleGUI.h"

#include "mmgr/mmgr.h"

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

	ret = App->file_system->SaveUnique(file, data, size, LIBRARY_MESH_FOLDER, path, "Tmesh");

	if (ret) 
	{ 
		LOG_C("NICE: Correctly exported %s.Tmesh into Meshes folder", path); 
	}
	else 
	{ 
		LOG_C("ERROR: Failed to export %s.Tmesh into Meshes folder", path); 
	}

	return ret;
}

bool Importer::Export(const char* path, std::string& file, ComponentTransform* transform)
{
	bool ret = false;

	uint size = sizeof(float3) * 3 + sizeof(float) * 32;

	char* data = new char[size];
	char* iterator = data;

	float3 transf[3] = { transform->position, transform->rotation, transform->scale };

	float matrix1[16], matrix2[16];

	int c = 0;

	for(int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			matrix1[c] = transform->localMatrix.At(i, j);
			matrix2[c] = transform->globalMatrix.At(i, j);

			c++;
		}

	// Storing position, rotation and scale
	uint bytes = sizeof(float3) * 3;
	memcpy(iterator, transf, bytes);

	// Storing Local Transformation
	iterator += bytes;
	bytes = sizeof(float) * 16;
	memcpy(iterator, matrix1, bytes);

	// Storing Global Transformation
	iterator += bytes;
	bytes = sizeof(float) * 16;
	memcpy(iterator, matrix2, bytes);

	ret = App->file_system->SaveUnique(file, data, size, LIBRARY_TRANSF_FOLDER, path, "Ttransf");

	if (ret)
	{
		LOG_C("NICE: Correctly exported %s.Ttransf into Transforms folder", path);
	}
	else
	{
		LOG_C("ERROR: Failed to export %s.Ttransf into Transforms folder", path);
	}

	return ret;
}