#include "ModuleImporter.h"
#include "MeshObj.h"
#include "Primitive.h"
#include "Application.h"
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
	return UPDATE_CONTINUE;
}

update_status ModuleImporter::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleImporter::CleanUp()
{
	aiDetachAllLogStreams();

	return true;
}

bool ModuleImporter::Load(const char* Filename)
{
	bool ret = true;

	const aiScene* scene = aiImportFile(Filename, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// mNumMeshes iterates on mMeshes[]
		for (int i = 0; i < scene->mNumMeshes && ret; ++i)
		{
			aiMesh* mesh2 = scene->mMeshes[i];

			MeshObj* meshObj = new MeshObj();
			ret = meshObj->Load(mesh2);
			meshes.push_back(meshObj);
		}

		aiReleaseImport(scene);
	}

	else
		App->appLogs.push_back("ERROR: Cannot load scene");

	return ret;
}

bool ModuleImporter::Draw()
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (int i = 0; i < meshes.size(); ++i)
	{
		MeshObj* meshObj = meshes[i];

		glEnableClientState(GL_VERTEX_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, meshObj->id_vertex);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshObj->id_index);

		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glDrawElements(GL_TRIANGLES, meshObj->num_index, GL_UNSIGNED_INT, NULL);

		glPopMatrix();
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableClientState(GL_VERTEX_ARRAY);

	}

	return true;
}