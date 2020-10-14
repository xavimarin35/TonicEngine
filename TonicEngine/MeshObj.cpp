#include "MeshObj.h"
#include "Application.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment ( lib, "Assimp/libx86/assimp.lib" )

MeshObj::MeshObj() { }

MeshObj::~MeshObj() { }

bool MeshObj::Load(aiMesh* mesh2)
{
	bool ret = true;

	// Vertices
	num_vertex = mesh2->mNumVertices;
	vertex = new float[num_vertex * 3];

	memcpy(vertex, mesh2->mVertices, sizeof(float) * num_vertex * 3);
	LOG("This mesh has %d vertices mi pana", num_vertex);

	glGenBuffers(1, &id_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex * 3, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Faces
	if (mesh2->HasFaces() && ret)
	{
		num_index = mesh2->mNumFaces * 3;
		index = new uint[num_index];

		for (uint j = 0; j < mesh2->mNumFaces; ++j)
		{
			{
				if (mesh2->mFaces[j].mNumIndices != 3)
				{
					LOG("Error in geometry face");

					ret = false;
				}

				else
				{
					memcpy(&index[j * 3], mesh2->mFaces[j].mIndices, 3 * sizeof(uint));
				}
			}
		}
	}

	// Indices
	glGenBuffers(1, &id_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3* num_index * sizeof(uint), index, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return ret;
}

void MeshObj::CleanUp()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}