#ifndef __MESH_IMPORTER_H__
#define __MESH_IMPORTER_H__

#include "Application.h"
#include "Module.h"
#include "ResourceMesh.h"

class aiNode;
class aiScene;
class Importer;
class GameObject;

class MeshImporter : public Module
{

public:
	MeshImporter(Application* app, bool start_enabled = true);
	~MeshImporter();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void LoadFile(const char* path, const char* texture_path = "Assets/Others/Lenna.png");
	void LoadNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* node_path, std::string output_file);

	bool Export(const char* name, std::string& output_file, uint num_index, uint* index, uint num_vertex, float3* vertex, uint num_normals, float3* face_center, float3* face_normal, uint num_tex_coords, float* tex_coords);
	bool Load(ResourceMesh* mesh);


public:
	bool active;

private:

	std::string TextureBuilding(int id);
	std::string GetOwnTexture(std::string objName, std::string texture_path);
	std::string GetMeshName(std::string name);
};

#endif