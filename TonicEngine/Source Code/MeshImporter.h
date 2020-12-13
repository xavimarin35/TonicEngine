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

	bool LoadFile(std::string path, std::string texture_path = "Assets/Others/Lenna.png");
	void LoadNode(const aiScene* scene, aiNode* node, const char* node_path, std::string output_file, GameObject* GO_root, std::string text_path);

	bool Export(const char* name, std::string& output_file, ResourceMesh* mesh);
	bool Load(ResourceMesh* mesh);

public:

	bool active = false;
};

#endif