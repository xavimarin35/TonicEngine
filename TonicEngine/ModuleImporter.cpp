#include "ModuleImporter.h"
#include "Application.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment ( lib, "Assimp/libx86/assimp.lib" )

ModuleImporter::ModuleImporter(Application* app, bool start_enabled) : Module(app, start_enabled) { enabled = true; }

ModuleImporter::~ModuleImporter() {}

bool ModuleImporter::Init()
{
	struct aiLogStream stream;

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);

	aiAttachLogStream(&stream);

	return true;
}

update_status ModuleImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

void ModuleImporter::Load(const char* Filename)
{
	const aiScene* scene = aiImportFile(Filename, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes()) // Loaded correctly
	{
		// mNumMeshes iterates on mMeshes[]
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			MeshObj* mesh = new MeshObj; 
			aiMesh* mesh2 = scene->mMeshes[i];

			mesh->num_vertex = mesh2->mNumVertices;
			mesh->vertex = new float3[mesh->num_vertex];

			for (uint i = 0; i < mesh2->mNumVertices; ++i)
			{
				mesh->vertex[i].x = mesh2->mVertices[i].x;
				mesh->vertex[i].y = mesh2->mVertices[i].y;
				mesh->vertex[i].z = mesh2->mVertices[i].z;
			}

			if (mesh2->HasFaces())
			{
				mesh->num_index = mesh2->mNumFaces * 3;
				mesh->index = new uint[mesh->num_index];

				for (uint i = 0; i < mesh2->mNumFaces; ++i)
				{
					if (mesh2->mFaces[i].mNumIndices != 3)
						App->appLogs.push_back("ERROR: Geometry face with != 3 indices");

					else
						memcpy(&mesh->index[i * 3], mesh2->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}

			if (mesh2->HasTextureCoords(0))
			{
				mesh->num_text_coords = mesh->num_vertex;
				mesh->text_coords = new float[mesh->num_text_coords * 2];

				for (int i = 0; i < mesh->num_text_coords; ++i)
				{
					mesh->text_coords[i * 2] = mesh2->mTextureCoords[0][i].x;
					mesh->text_coords[(i * 2) + 1] = mesh2->mTextureCoords[0][i].y;
				}
			}

			App->renderer3D->NewVertexBuffer(mesh->vertex, mesh->num_vertex, mesh->id_vertex);
			App->renderer3D->NewIndexBuffer(mesh->index, mesh->num_index, mesh->id_index);
			App->renderer3D->NewTextBuffer(mesh->text_coords, mesh->num_text_coords, mesh->id_text_coords);

			meshes.push_back(mesh);

		}

		aiReleaseImport(scene);
		App->appLogs.push_back("Succesfully loaded mesh");
	}

	else
		App->appLogs.push_back("ERROR: Cannot load scene");
}