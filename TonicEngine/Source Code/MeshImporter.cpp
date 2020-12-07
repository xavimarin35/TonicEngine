#include "MeshImporter.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "GameObject.h"
#include "ModuleSceneIntro.h"
#include "ModuleFileSystem.h"
#include "Importer.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ModuleResources.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma coment (lib, "Assimp/libx86/assimp.lib")

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

void MeshImporter::LoadFile(const char* path, const char* texture_path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr)
	{
		aiNode* root_node = scene->mRootNode;

		GameObject* Empty = App->scene_intro->CreateGO(App->GetPathName(path));

		/*Importer ex;*/ std::string file;

		App->scene_intro->GOroot->AddChild(Empty);

		if (root_node->mNumChildren > 0)
			for (int i = 0; i < root_node->mNumChildren; ++i)
				LoadNode(scene, root_node->mChildren[i], Empty, path, file);

		aiReleaseImport(scene);

		LOG_C("Succesfully loaded mesh with path: %s", path);
	}
	else LOG_C("ERROR: Could not load scene with path: %s", path);
}

void MeshImporter::LoadNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* node_path, std::string output_file)
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

	GameObject* obj = App->scene_intro->CreateGO(node_name);
	ComponentTransform* transf = obj->GetComponentTransform();

	transf->position = pos2;
	transf->scale = s2;
	transf->rotation_quaternion = rot2;

	transf->UpdateLocalTransform();

	obj->GetComponentTransform()->default_position = transf->position;
	obj->GetComponentTransform()->default_rotation_e = transf->rotation_euler;
	obj->GetComponentTransform()->default_rotation_q= transf->rotation_quaternion;
	obj->GetComponentTransform()->default_scale = transf->scale;

	parent->AddChild(obj);

	for (int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* new_mesh = scene->mMeshes[node->mMeshes[i]];

		GameObject* child = nullptr;
		if (node->mNumMeshes > 1)
		{
			node_name = new_mesh->mName.C_Str();
			if (node_name == "")
				node_name = obj->data.name + "";

			if (i > 0)
				node_name.append("(" + std::to_string(i) + ")");

			child = App->scene_intro->CreateGO(node_name);
			obj->AddChild(child);
		}
		else
		{
			child = obj;
		}

		child->CreateComponent(COMPONENT_TYPE::MESH);
		//child->CreateComponent(COMPONENT_TYPE::TEXTURE);
		ComponentMesh* mesh = child->GetComponentMesh();
		
		aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];
		uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

		aiString path; // = "D:\GitHub\TonicEngine\TonicEngine\Tonic Engine\Game\Assets\Street";
		material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		if (path.C_Str() != nullptr && path.length > 0)
		{
			child->CreateComponent(COMPONENT_TYPE::TEXTURE);
			std::string dir = App->GetPathDir(node_path);
			dir.append("/");
			dir.append(path.C_Str());

			child->GetComponentTexture()->rTexture = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile(dir.c_str()));
			//App->tex_imp->LoadTexture(GetOwnTexture(child->data.name, texture_path).c_str());
			if (child->GetComponentTexture()->rTexture != nullptr)
				child->GetComponentTexture()->rTexture->LoadInMemory();
		}
		else child->GetComponentTexture()->texture = App->tex_imp->checker_texture;

		mesh->mData.num_vertex = new_mesh->mNumVertices;
		mesh->mData.vertex = new float3[mesh->mData.num_vertex];

		for (uint i = 0; i < new_mesh->mNumVertices; ++i)
		{
			mesh->mData.vertex[i].x = new_mesh->mVertices[i].x;
			mesh->mData.vertex[i].y = new_mesh->mVertices[i].y;
			mesh->mData.vertex[i].z = new_mesh->mVertices[i].z;
		}

		bool indices3 = true;

		// Faces
		if (new_mesh->HasFaces())
		{
			mesh->mData.num_index = new_mesh->mNumFaces * 3;
			mesh->mData.index = new uint[mesh->mData.num_index];
			for (uint i = 0; i < new_mesh->mNumFaces; ++i)
			{
				if (new_mesh->mFaces[i].mNumIndices != 3)
				{
					indices3 = false;
					LOG_C("WARNING: A face with != 3 indices of this mesh %s", obj->data.name.c_str());
				}
				else
					memcpy(&mesh->mData.index[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}

		// Normals
		if (new_mesh->HasNormals() && indices3)
		{
			mesh->mData.face_center = new float3[mesh->mData.num_index];
			mesh->mData.normals = new float3[mesh->mData.num_index];
			mesh->mData.num_normals = mesh->mData.num_index / 3;

			for (uint j = 0; j < mesh->mData.num_index / 3; ++j)
			{
				float3 face_A, face_B, face_C;

				face_A = mesh->mData.vertex[mesh->mData.index[j * 3]];
				face_B = mesh->mData.vertex[mesh->mData.index[(j * 3) + 1]];
				face_C = mesh->mData.vertex[mesh->mData.index[(j * 3) + 2]];

				mesh->mData.face_center[j] = (face_A + face_B + face_C) / 3;

				float3 edge1 = face_B - face_A;
				float3 edge2 = face_C - face_A;

				mesh->mData.normals[j] = Cross(edge1, edge2);
				mesh->mData.normals[j].Normalize();
				mesh->mData.normals[j] *= 0.15f;
			}
		}

		if (new_mesh->HasTextureCoords(0))
		{
			mesh->mData.num_tex_coords = mesh->mData.num_vertex;
			mesh->mData.tex_coords = new float[mesh->mData.num_tex_coords * 2];

			for (int i = 0; i < mesh->mData.num_tex_coords; ++i)
			{
				mesh->mData.tex_coords[i * 2] = new_mesh->mTextureCoords[0][i].x;
				mesh->mData.tex_coords[(i * 2) + 1] = new_mesh->mTextureCoords[0][i].y;
			}
		}

		mesh->aabb.SetNegativeInfinity();
		mesh->aabb = mesh->aabb.MinimalEnclosingAABB(mesh->mData.vertex, mesh->mData.num_vertex);

		//Generate the buffers 
		App->renderer3D->VertexBuffer(mesh->mData.vertex, mesh->mData.num_vertex, mesh->mData.id_vertex);
		App->renderer3D->IndexBuffer(mesh->mData.index, mesh->mData.num_index, mesh->mData.id_index);
		App->renderer3D->TextureBuffer(mesh->mData.tex_coords, mesh->mData.num_tex_coords, mesh->mData.id_tex_coords);
	}

	if (node->mNumChildren > 0)
		for (int i = 0; i < node->mNumChildren; ++i)
			LoadNode(scene, node->mChildren[i], obj, node_path, output_file);
}

bool MeshImporter::Export(const char* name, std::string& output_file, uint num_index, uint* index, uint num_vertex, float3* vertex, uint num_normals, float3* face_center, float3* face_normal, uint num_tex_coords, float* tex_coords)
{
	bool ret = false;

	// amount of indices / vertices / normals / texture_coords / AABB
	uint ranges[4] = { num_index, num_vertex,  num_normals, num_tex_coords };

	uint size = sizeof(ranges) + sizeof(uint) * num_index + sizeof(float) * num_vertex * 3 + sizeof(float) * num_normals * 3 * 2 + sizeof(float) * num_tex_coords * 2;

	char* data = new char[size]; // Allocate
	char* cursor = data;

	uint bytes = sizeof(ranges); // First store ranges
	memcpy(cursor, ranges, bytes);

	cursor += bytes; // Store indices
	bytes = sizeof(uint) * num_index;
	memcpy(cursor, index, bytes);

	cursor += bytes; // Store Vertices
	bytes = sizeof(float) * num_vertex * 3;
	memcpy(cursor, vertex, bytes);

	cursor += bytes; // Store Normals Starting Point
	bytes = sizeof(float) * num_normals * 3;
	memcpy(cursor, face_center, bytes);

	cursor += bytes; // Store Normals Vector
	bytes = sizeof(float) * num_normals * 3;
	memcpy(cursor, face_normal, bytes);

	cursor += bytes; // Store Texture Coordinates
	bytes = sizeof(float) * num_tex_coords * 2;
	memcpy(cursor, tex_coords, bytes);


	ret = App->file_system->SaveUnique(output_file, data, size, LIBRARY_MESH_FOLDER, name, "mesh");

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
	App->file_system->Load(mesh->exported_file.c_str(), &buffer); //put data file in buffer

	if (buffer)
	{
		char* cursor = buffer;

		// amount of indices / vertices / normals / texture_coords
		uint ranges[4];
		uint bytes = sizeof(ranges);
		memcpy(ranges, cursor, bytes);

		mesh->data.num_index = ranges[0];
		mesh->data.num_vertex = ranges[1];
		mesh->data.num_normals = ranges[2];
		mesh->data.num_tex_coords = ranges[3];

		cursor += bytes; // Load indices
		bytes = sizeof(uint) * mesh->data.num_index;
		mesh->data.index = new uint[mesh->data.num_index];
		memcpy(mesh->data.index, cursor, bytes);

		cursor += bytes; // Load vertex
		bytes = sizeof(float) * mesh->data.num_vertex * 3;
		mesh->data.vertex = new float3[mesh->data.num_vertex];
		memcpy(mesh->data.vertex, cursor, bytes);

		cursor += bytes; // Load Normals Starting Point
		bytes = sizeof(float) * mesh->data.num_normals * 3;
		mesh->data.face_center = new float3[mesh->data.num_normals];
		memcpy(mesh->data.face_center, cursor, bytes);

		cursor += bytes; // Load Normals Vector
		bytes = sizeof(float) * mesh->data.num_normals * 3;
		mesh->data.face_normal = new float3[mesh->data.num_normals];
		memcpy(mesh->data.face_normal, cursor, bytes);

		cursor += bytes; // Load Texture Coordinates
		bytes = sizeof(float) * mesh->data.num_tex_coords * 2;
		mesh->data.tex_coords = new float[mesh->data.num_tex_coords * 2];
		memcpy(mesh->data.tex_coords, cursor, bytes);

		//Generate the buffers 
		App->renderer3D->VertexBuffer(mesh->data.vertex, mesh->data.num_vertex, mesh->data.id_vertex);
		App->renderer3D->IndexBuffer(mesh->data.index, mesh->data.num_index, mesh->data.id_index);
		App->renderer3D->TextureBuffer(mesh->data.tex_coords, mesh->data.num_tex_coords, mesh->data.id_tex_coords);

		RELEASE_ARRAY(buffer);
		cursor = nullptr;

		ret = true;
	}
	return ret;
}

std::string MeshImporter::TextureBuilding(int id)
{
	std::string path;

	switch (id)
	{
	case 1:
		path = "Assets/Street/building01.png";
		break;
	case 2:
		path = "Assets/Street/building02.png";
		break;
	case 3:
		path = "Assets/Street/building03.png";
		break;
	case 4:
		path = "Assets/Street/building04.png";
		break;
	case 5:
		path = "Assets/Street/building05.png";
		break;
	case 6:
		path = "Assets/Street/building06.png";
		break;
	case 7:
		path = "Assets/Street/building07.png";
		break;
	case 8:
		path = "Assets/Street/building08.png";
		break;
	case 10:
		path = "Assets/Others/plane_tex.png";
		break;
	}

	return path;
}

std::string MeshImporter::GetOwnTexture(std::string objName, std::string texture_path)
{
	std::string newPath;

	if (objName.find("Plane") == std::string::npos)
		newPath = App->GetBuildingID(objName);
	else
		newPath = App->GetBuildingID(objName, "Plane");
	
	if (newPath == objName)
		return texture_path;
	else
	{
		int id = std::stoi(newPath);
		return TextureBuilding(id).c_str();
	}
}

std::string MeshImporter::GetMeshName(std::string name)
{
	size_t num = name.find_last_of("_");

	std::string path = name.substr(0, num);

	return path;
}