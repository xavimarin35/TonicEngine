#include "MeshImporter.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "GameObject.h"
#include "ModuleSceneIntro.h"
#include "ModuleFileSystem.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ModuleResources.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

MeshImporter::MeshImporter(Application* app, bool start_enabled) : Module(app, start_enabled) 
{ 
	active = true; 
}

MeshImporter::~MeshImporter() 
{
}

bool MeshImporter::Init()
{
	struct aiLogStream stream;

	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);

	aiAttachLogStream(&stream);

	if (aiGetErrorString() != NULL)
	{
		LOG_C("Initializing ASSIMP");
	}
	else
	{
		LOG_C("ERROR: Could not initialize ASSIMP");
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

bool MeshImporter::LoadFile(std::string path, std::string texture_path)
{
	const aiScene* scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr)
	{
		aiNode* node = scene->mRootNode;
		std::string file;

		GameObject* GO = App->scene_intro->CreateGO(App->GetPathName(path));
		App->scene_intro->GOroot->AddChild(GO);

		if (node->mNumChildren > 0)
			for (int i = 0; i < node->mNumChildren; ++i)
				LoadNode(scene, node->mChildren[i], path.c_str(), file, GO, texture_path.c_str());

		aiReleaseImport(scene);

		LOG_C("Succesfully loaded mesh with path: %s", path);
	}
	else LOG_C("ERROR: Could not load scene with path: %s", path);

	return true;
}

void MeshImporter::LoadNode(const aiScene* scene, aiNode* node, const char* node_path, std::string output_file, GameObject* GO_root, std::string text_path)
{
	aiVector3D translation, scaling;
	aiQuaternion rotation;

	node->mTransformation.Decompose(scaling, rotation, translation);

	float3 pos2(translation.x, translation.y, translation.z);
	float3 s2(1, 1, 1);
	Quat rot2(rotation.x, rotation.y, rotation.z, rotation.w);

	std::string node_name = node->mName.C_Str();

	bool dummyMesh = true;

	while (dummyMesh)
	{
		if (node_name.find("_$AssimpFbx$_") != std::string::npos && node->mNumChildren == 1)
		{
			node = node->mChildren[0];

			node->mTransformation.Decompose(scaling, rotation, translation);
			pos2 += float3(translation.x, translation.y, translation.z);
			s2 = float3(s2.x * scaling.x, s2.y * scaling.y, s2.z * scaling.z);
			rot2 = rot2 * Quat(rotation.x, rotation.y, rotation.z, rotation.w);

			node_name = node->mName.C_Str();
			dummyMesh = true;
		}
		else
			dummyMesh = false;
	}

	GameObject* go = App->scene_intro->CreateGO(node_name);
	ComponentTransform* transf = go->GetComponentTransform();

	transf->position = pos2;
	transf->scale = s2;
	transf->rotation_quaternion = rot2;
	transf->rotation_euler = rot2.ToEulerXYZ() * RADTODEG;

	transf->UpdateLocalTransform();

	if (App->gui->CheckParent(GO_root))
	{
		go->GetComponentTransform()->default_position = transf->position;
		go->GetComponentTransform()->default_rotation_e = transf->rotation_euler;
		go->GetComponentTransform()->default_rotation_q = transf->rotation_quaternion;
		go->GetComponentTransform()->default_scale = transf->scale;
	}
	else
	{
		go->GetComponentTransform()->default_position = float3::zero;
		go->GetComponentTransform()->default_rotation_e = float3::zero;
		go->GetComponentTransform()->default_rotation_q = Quat::identity;
		go->GetComponentTransform()->default_scale = float3::one;
	}

	GO_root->AddChild(go);
	go->GetComponentTransform()->Reset();

	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* new_mesh = scene->mMeshes[node->mMeshes[i]];

		GameObject* child = nullptr;
		if (node->mNumMeshes > 1)
		{
			node_name = new_mesh->mName.C_Str();
			if (node_name == "")
				node_name = go->data.name + "";

			if (i > 0)
				node_name.append("(" + std::to_string(i) + ")");

			child = App->scene_intro->CreateGO(node_name);
			go->AddChild(child);
		}

		else
		{
			child = go;
		}

		child->CreateComponent(COMPONENT_TYPE::MESH);
		ComponentMesh* mesh = child->GetComponentMesh();

		if (App->resources->GetResourceFromFolder(Assets::FOLDERS::LIBRARY, child->data.name.c_str()) != NULL)
		{
			mesh->rMesh = (ResourceMesh*)App->resources->Get(App->resources->GetResourceFromFolder(Assets::FOLDERS::LIBRARY, child->data.name.c_str()));

			if (mesh->rMesh != nullptr)
				mesh->rMesh->LoadInMemory();
		}

		else
		{
			ResourceMesh* res_mesh = (ResourceMesh*)App->resources->CreateResource(RESOURCE_TYPE::MESH);

			res_mesh->data.num_vertex = new_mesh->mNumVertices;
			res_mesh->data.vertex = new float3[res_mesh->data.num_vertex];

			for (uint i = 0; i < new_mesh->mNumVertices; ++i)
			{
				res_mesh->data.vertex[i].x = new_mesh->mVertices[i].x;
				res_mesh->data.vertex[i].y = new_mesh->mVertices[i].y;
				res_mesh->data.vertex[i].z = new_mesh->mVertices[i].z;
			}

			// Faces
			if (new_mesh->HasFaces())
			{
				res_mesh->data.num_index = new_mesh->mNumFaces * 3;
				res_mesh->data.index = new uint[res_mesh->data.num_index];
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						res_mesh->data.indices3 = false;
						LOG_C("WARNING: mesh %s geometry face with != 3 indices!", go->data.name.c_str());
					}
					else
						memcpy(&res_mesh->data.index[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}

			// Normals
			if (new_mesh->HasNormals() && res_mesh->data.indices3)
			{
				res_mesh->data.face_center = new float3[res_mesh->data.num_index];
				res_mesh->data.face_normals = new float3[res_mesh->data.num_index];
				res_mesh->data.num_normals = res_mesh->data.num_index / 3;
				for (uint j = 0; j < res_mesh->data.num_index / 3; ++j)
				{
					float3 face_A, face_B, face_C;


					face_A = res_mesh->data.vertex[res_mesh->data.index[j * 3]];
					face_B = res_mesh->data.vertex[res_mesh->data.index[(j * 3) + 1]];
					face_C = res_mesh->data.vertex[res_mesh->data.index[(j * 3) + 2]];


					res_mesh->data.face_center[j] = (face_A + face_B + face_C) / 3;


					float3 edge1 = face_B - face_A;
					float3 edge2 = face_C - face_A;

					res_mesh->data.face_normals[j] = Cross(edge1, edge2);
					res_mesh->data.face_normals[j].Normalize();
					res_mesh->data.face_normals[j] *= 0.15f;

				}
			}

			// UVs
			if (new_mesh->HasTextureCoords(0))
			{
				res_mesh->data.num_tex_coords = res_mesh->data.num_vertex;
				res_mesh->data.tex_coords = new float[res_mesh->data.num_tex_coords * 2];

				for (int i = 0; i < res_mesh->data.num_tex_coords; ++i)
				{
					res_mesh->data.tex_coords[i * 2] = new_mesh->mTextureCoords[0][i].x;
					res_mesh->data.tex_coords[(i * 2) + 1] = new_mesh->mTextureCoords[0][i].y;
				}
			}

			Export(child->data.name.c_str(), res_mesh->exported_file, res_mesh);
			res_mesh->file = node_path;

			mesh->rMesh = res_mesh;

			if(mesh->rMesh != nullptr)
				mesh->rMesh->LoadInMemory();
		}
		
		aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];
		uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

		aiString path;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		if (mesh != nullptr)
		{
			mesh->aabb.SetNegativeInfinity();
			mesh->aabb = mesh->aabb.MinimalEnclosingAABB(mesh->rMesh->data.vertex, mesh->rMesh->data.num_vertex);
		}

		if (path.C_Str() != nullptr && path.length > 0)
		{
			child->CreateComponent(COMPONENT_TYPE::TEXTURE);
			std::string dir = App->GetPathDir(node_path);
			dir.append("/");
			dir.append(path.C_Str());

			child->GetComponentTexture()->rTexture = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile(dir.c_str()));
			if (child->GetComponentTexture()->rTexture != nullptr)
				child->GetComponentTexture()->rTexture->LoadInMemory();
		}
		else
		{
			child->CreateComponent(COMPONENT_TYPE::TEXTURE);

			child->GetComponentTexture()->rTexture = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile(text_path.c_str()));

			if (child->GetComponentTexture()->rTexture != nullptr)
				child->GetComponentTexture()->rTexture->LoadInMemory();
		}
	}

	if (node->mNumChildren > 0)
		for (int i = 0; i < node->mNumChildren; ++i)
			LoadNode(scene, node->mChildren[i], node_path, output_file, go, text_path);
}

bool MeshImporter::Export(const char* name, std::string& output_file, ResourceMesh* mesh)
{
	bool ret = false;

	uint ranges[4] = { mesh->data.num_index, mesh->data.num_vertex,  mesh->data.num_normals, mesh->data.num_tex_coords };

	uint size = sizeof(ranges) 
		+ sizeof(uint) * mesh->data.num_index 
		+ sizeof(float) * mesh->data.num_vertex * 3 
		+ sizeof(float) * mesh->data.num_normals * 3 * 2 
		+ sizeof(float) * mesh->data.num_tex_coords * 2;

	char* data = new char[size]; 
	char* cursor = data;

	uint bytes = sizeof(ranges); 
	memcpy(cursor, ranges, bytes);

	cursor += bytes; 
	bytes = sizeof(uint) * mesh->data.num_index;
	memcpy(cursor, mesh->data.index, bytes);

	cursor += bytes; 
	bytes = sizeof(float) * mesh->data.num_vertex * 3;
	memcpy(cursor, mesh->data.vertex, bytes);

	cursor += bytes; 
	bytes = sizeof(float) * mesh->data.num_normals * 3;
	memcpy(cursor, mesh->data.face_center, bytes);

	cursor += bytes; 
	bytes = sizeof(float) * mesh->data.num_normals * 3;
	memcpy(cursor, mesh->data.face_normals, bytes);

	cursor += bytes;
	bytes = sizeof(float) * mesh->data.num_tex_coords * 2;
	memcpy(cursor, mesh->data.tex_coords, bytes);


	ret = App->file_system->SaveUnique(output_file, data, size, LIBRARY_MESH_FOLDER, name, "Tmesh");

	if (!ret)
		LOG_C("Failed exporting %s.tmesh into Library/Meshes floder", name);

	if (data)
	{
		delete[] data;
		data = nullptr;
		cursor = nullptr;
	}

	return ret;
}

bool MeshImporter::Load(ResourceMesh* mesh)
{
	bool ret = true;

	char* buffer = nullptr;
	App->file_system->Load(mesh->exported_file.c_str(), &buffer);

	if (buffer)
	{
		char* cursor = buffer;

		uint ranges[4];
		uint bytes = sizeof(ranges);
		memcpy(ranges, cursor, bytes);

		mesh->data.num_index = ranges[0];
		mesh->data.num_vertex = ranges[1];
		mesh->data.num_normals = ranges[2];
		mesh->data.num_tex_coords = ranges[3];

		cursor += bytes; 
		bytes = sizeof(uint) * mesh->data.num_index;
		mesh->data.index = new uint[mesh->data.num_index];
		memcpy(mesh->data.index, cursor, bytes);

		cursor += bytes; 
		bytes = sizeof(float) * mesh->data.num_vertex * 3;
		mesh->data.vertex = new float3[mesh->data.num_vertex];
		memcpy(mesh->data.vertex, cursor, bytes);

		cursor += bytes; 
		bytes = sizeof(float) * mesh->data.num_normals * 3;
		mesh->data.face_center = new float3[mesh->data.num_normals];
		memcpy(mesh->data.face_center, cursor, bytes);

		cursor += bytes; 
		bytes = sizeof(float) * mesh->data.num_normals * 3;
		mesh->data.face_normals = new float3[mesh->data.num_normals];
		memcpy(mesh->data.face_normals, cursor, bytes);

		cursor += bytes; 
		bytes = sizeof(float) * mesh->data.num_tex_coords * 2;
		mesh->data.tex_coords = new float[mesh->data.num_tex_coords * 2];
		memcpy(mesh->data.tex_coords, cursor, bytes);

		// Generate buffers with all mesh info
		App->renderer3D->VertexBuffer(mesh->data.vertex, mesh->data.num_vertex, mesh->data.id_vertex);
		App->renderer3D->IndexBuffer(mesh->data.index, mesh->data.num_index, mesh->data.id_index);
		App->renderer3D->TextureBuffer(mesh->data.tex_coords, mesh->data.num_tex_coords, mesh->data.id_tex_coords);

		RELEASE_ARRAY(buffer);
		cursor = nullptr;

		ret = true;
	}
	return ret;
}