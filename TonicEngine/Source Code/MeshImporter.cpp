#include "MeshImporter.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "GameObject.h"
#include "ModuleSceneIntro.h"
#include "ModuleFileSystem.h"
#include "Importer.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment ( lib, "Assimp/libx86/assimp.lib" )

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

	if (scene != nullptr && scene->HasMeshes())
	{
		aiNode* root_node = scene->mRootNode;

		GameObject* Empty = App->scene_intro->CreateGO(App->GetPathName(path));

		aiVector3D translation, scaling;
		aiQuaternion rotation;

		root_node->mTransformation.Decompose(scaling, rotation, translation);

		float3 position(translation.x, translation.y, translation.z);
		float3 sc(1, 1, 1);
		Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

		Empty->GetComponentTransform()->position = position;
		Empty->GetComponentTransform()->scale = sc;
		Empty->GetComponentTransform()->rotation_quaternion = rot;

		Empty->GetComponentTransform()->UpdateLocalTransform();

		Importer ex; std::string file;

		App->scene_intro->GOroot->AddChild(Empty);

		if (root_node->mNumChildren > 0)
			for (int i = 0; i < root_node->mNumChildren; ++i)
				LoadNode(scene, root_node->mChildren[i], Empty, path, ex, file, texture_path);

		aiReleaseImport(scene);

		LOG_C("Succesfully loaded mesh with path: %s", path);
	}
	else LOG_C("ERROR: Could not load scene with path: %s", path);
}

void MeshImporter::LoadNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* path, Importer ex, std::string file, const char* texture_path)
{
	if (node != nullptr && node->mNumMeshes > 0)
	{
		for (int i = 0; i < node->mNumMeshes; ++i)
		{
			GameObject* obj = App->scene_intro->CreateGO(node->mName.C_Str());

			obj->CreateComponent(COMPONENT_TYPE::MESH);
			obj->CreateComponent(COMPONENT_TYPE::TEXTURE);

			ComponentMesh* mesh = obj->GetComponentMesh();
			ComponentTransform* transform = obj->GetComponentTransform();

			parent->AddChild(obj);

			aiNode* new_node = node;

			aiVector3D translation, scaling;
			aiQuaternion rotation;

			new_node->mTransformation.Decompose(scaling, rotation, translation);

			float3 pos(translation.x, translation.y, translation.z);
			float3 sc(1, 1, 1);
			Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

			obj->GetComponentTransform()->position = pos;
			obj->GetComponentTransform()->scale = sc;
			obj->GetComponentTransform()->rotation_quaternion = rot;

			obj->GetComponentTransform()->UpdateLocalTransform();

			aiMesh* mesh2 = scene->mMeshes[new_node->mMeshes[i]];

			aiMaterial* material1 = scene->mMaterials[mesh2->mMaterialIndex];
			uint numTextures = material1->GetTextureCount(aiTextureType_DIFFUSE);

			aiString pathStr;
			material1->GetTexture(aiTextureType_DIFFUSE, 0, &pathStr);

			if (pathStr.C_Str() != nullptr)
			{
				obj->GetComponentTexture()->texture = App->tex_imp->LoadTexture(GetOwnTexture(obj->data.name, texture_path).c_str());
			}
			else obj->GetComponentTexture()->texture = App->tex_imp->checker_texture;


			// Copy vertices
			mesh->mData.num_vertex = mesh2->mNumVertices;
			mesh->mData.vertex = new float3[mesh->mData.num_vertex];

			for (uint i = 0; i < mesh2->mNumVertices; ++i)
			{
				mesh->mData.vertex[i].x = mesh2->mVertices[i].x;
				mesh->mData.vertex[i].y = mesh2->mVertices[i].y;
				mesh->mData.vertex[i].z = mesh2->mVertices[i].z;
			}

			bool indices_work = true;

			// Copy faces
			if (mesh2->HasFaces())
			{
				mesh->mData.num_index = mesh2->mNumFaces * 3;
				mesh->mData.index = new uint[mesh->mData.num_index]; // Each face has a triangle
				for (uint i = 0; i < mesh2->mNumFaces; ++i)
				{
					if (mesh2->mFaces[i].mNumIndices != 3)
					{
						indices_work = false;
						LOG_C("WARNING: Geometry face with != 3 indices!");
					}
					else
						memcpy(&mesh->mData.index[i * 3], mesh2->mFaces[i].mIndices, 3 * sizeof(uint));
				}
			}
			
			// Normals
			if (mesh2->HasNormals() && indices_work)
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

			if (mesh2->HasTextureCoords(0))
			{
				mesh->mData.num_tex_coords = mesh->mData.num_vertex;
				mesh->mData.tex_coords = new float[mesh->mData.num_tex_coords * 2];

				for (int i = 0; i < mesh->mData.num_tex_coords; ++i)
				{
					mesh->mData.tex_coords[i * 2] = mesh2->mTextureCoords[0][i].x;
					mesh->mData.tex_coords[(i * 2) + 1] = mesh2->mTextureCoords[0][i].y;
				}
			}

			App->renderer3D->VertexBuffer(mesh->mData.vertex, mesh->mData.num_vertex, mesh->mData.id_vertex);
			App->renderer3D->IndexBuffer(mesh->mData.index, mesh->mData.num_index, mesh->mData.id_index);
			App->renderer3D->TextureBuffer(mesh->mData.tex_coords, mesh->mData.num_tex_coords, mesh->mData.id_tex_coords);

			const char* name = obj->data.name.c_str();

			ex.Export(name, file, obj->GetComponentMesh());
			obj->GetComponentMesh()->mData.path = file;
		}
	}

	if (node->mNumChildren > 0)
		for (int i = 0; i < node->mNumChildren; ++i)
			LoadNode(scene, node->mChildren[i], parent, path, ex, file, texture_path);
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

	if (objName != "g Plane001")
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