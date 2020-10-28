#include "MeshImporter.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "GameObject.h"
#include "ModuleSceneIntro.h"


#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment ( lib, "Assimp/libx86/assimp.lib" )

MeshImporter::MeshImporter(Application* app, bool start_enabled) : Module(app, start_enabled) { enabled = true; }

MeshImporter::~MeshImporter() {}

bool MeshImporter::Init()
{
	struct aiLogStream stream;

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);

	aiAttachLogStream(&stream);

	if (aiGetErrorString() != NULL)
	{
		LOG_IMGUI_CONSOLE("Initializing ASSIMP");
	}
	else
	{
		LOG_IMGUI_CONSOLE("ERROR: Could not initialize ASSIMP");
		return false;
	}

	return true;
}

update_status MeshImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool MeshImporter::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

void MeshImporter::LoadMesh(const char* Filename)
{
	const aiScene* scene = aiImportFile(Filename, aiProcessPreset_TargetRealtime_MaxQuality);


	if (scene != nullptr && scene->HasMeshes()) // Loaded correctly
	{
		// mNumMeshes iterates on mMeshes[]
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			GameObject* meshGO = App->scene_intro->CreateGO("GameObject_");

			aiMesh* mesh2 = scene->mMeshes[i];

			meshGO->GetComponentMesh()->mData.path = Filename;

			meshGO->GetComponentMesh()->mData.num_vertex = mesh2->mNumVertices;
			meshGO->GetComponentMesh()->mData.vertex = new float3[meshGO->GetComponentMesh()->mData.num_vertex];

			for (uint i = 0; i < mesh2->mNumVertices; ++i)
			{
				meshGO->GetComponentMesh()->mData.vertex[i].x = mesh2->mVertices[i].x;
				meshGO->GetComponentMesh()->mData.vertex[i].y = mesh2->mVertices[i].y;
				meshGO->GetComponentMesh()->mData.vertex[i].z = mesh2->mVertices[i].z;
			}

			if (mesh2->HasFaces())
			{
				meshGO->GetComponentMesh()->mData.num_index = mesh2->mNumFaces * 3;
				meshGO->GetComponentMesh()->mData.index = new uint[meshGO->GetComponentMesh()->mData.num_index];

				for (uint i = 0; i < mesh2->mNumFaces; ++i)
				{
					if (mesh2->mFaces[i].mNumIndices != 3)
					{
						LOG_IMGUI_CONSOLE("ERROR: Geometry face with != 3 indices");
					}
					else
						memcpy(&meshGO->GetComponentMesh()->mData.index[i * 3], mesh2->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}

			if (mesh2->HasTextureCoords(0))
			{
				meshGO->GetComponentMesh()->mData.num_tex_coords = meshGO->GetComponentMesh()->mData.num_vertex;
				meshGO->GetComponentMesh()->mData.tex_coords = new float[meshGO->GetComponentMesh()->mData.num_tex_coords * 2];

				for (int i = 0; i < meshGO->GetComponentMesh()->mData.num_tex_coords; ++i)
				{
					meshGO->GetComponentMesh()->mData.tex_coords[i * 2] = mesh2->mTextureCoords[0][i].x;
					meshGO->GetComponentMesh()->mData.tex_coords[(i * 2) + 1] = mesh2->mTextureCoords[0][i].y;
				}
			}

			App->renderer3D->NewVertexBuffer(meshGO->GetComponentMesh()->mData.vertex, meshGO->GetComponentMesh()->mData.num_vertex, meshGO->GetComponentMesh()->mData.id_vertex);
			App->renderer3D->NewIndexBuffer(meshGO->GetComponentMesh()->mData.index, meshGO->GetComponentMesh()->mData.num_index, meshGO->GetComponentMesh()->mData.id_index);
			App->renderer3D->NewTextBuffer(meshGO->GetComponentMesh()->mData.tex_coords, meshGO->GetComponentMesh()->mData.num_tex_coords, meshGO->GetComponentMesh()->mData.id_tex_coords);

		}

		aiReleaseImport(scene);
		LOG_IMGUI_CONSOLE("Succesfully loaded mesh with path: %s", Filename);
	}

	else
		LOG_IMGUI_CONSOLE("ERROR: Cannot load scene %s", Filename);
}