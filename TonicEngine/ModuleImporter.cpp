#include "ModuleImporter.h"
#include "MeshObj.h"
#include "Primitive.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "SDL/include/SDL.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment ( lib, "Assimp/libx86/assimp.lib" )

ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled) 
{
	enabled = true;
}

ModuleImporter::~ModuleImporter() {}

bool ModuleImporter::Start()
{
	struct aiLogStream stream;

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);

	aiAttachLogStream(&stream);

	// Load("Assets/warrior.FBX");

	return true;
}

update_status ModuleImporter::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleImporter::Update(float dt)
{
	for (int i = 0; i < meshes.size(); ++i)
	{
		App->renderer3D->Draw(meshes[i]);
	}
	return UPDATE_CONTINUE;
}

update_status ModuleImporter::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();

	meshes.clear();

	return true;
}

bool ModuleImporter::Load(const char* Filename)
{
	bool ret = true;

	const aiScene* scene = aiImportFile(Filename, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) // Loaded correctly
	{
		// mNumMeshes iterates on mMeshes[]
		for (int i = 0; i < scene->mNumMeshes && ret; ++i)
		{
			aiMesh* mesh2 = scene->mMeshes[i];

			MeshObj* meshObj = new MeshObj();

			meshObj->num_vertex = mesh2->mNumVertices;
			meshObj->vertex = new float[meshObj->num_vertex * 3];

			memcpy(meshObj->vertex, mesh2->mVertices, sizeof(float) * meshObj->num_vertex * 3);
			App->appLogs.push_back("New mesh loaded");

			if (mesh2->HasFaces())
			{
				meshObj->num_index = mesh2->mNumFaces * 3;
				meshObj->index = new uint[meshObj->num_index];

				for (uint i = 0; i < mesh2->mNumFaces; ++i)
				{
					if (mesh2->mFaces[i].mNumIndices != 3)
						App->appLogs.push_back("ERROR: Geometry face with != 3 indices");

					else
						memcpy(&meshObj->index[i * 3], mesh2->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}

			App->renderer3D->NewVertexBuffer(meshObj->vertex, meshObj->num_vertex, meshObj->id_vertex);
			App->renderer3D->NewIndexBuffer(meshObj->index, meshObj->num_index, meshObj->id_index);

			meshes.push_back(meshObj);

		}

		aiReleaseImport(scene);
	}

	else
		App->appLogs.push_back("ERROR: Cannot load scene");

	return ret;
}