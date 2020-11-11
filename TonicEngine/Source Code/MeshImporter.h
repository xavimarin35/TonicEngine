#ifndef __MESH_IMPORTER_H__
#define __MESH_IMPORTER_H__

#include "Application.h"
#include "Module.h"

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

	void LoadFile(const char* path);
	void LoadNode(const aiScene* scene, aiNode* node, GameObject* parent, const char* path, Importer ex, std::string file);

public:
	bool active;
};

#endif