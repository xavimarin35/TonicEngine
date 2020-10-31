#ifndef __MESH_IMPORTER_H__
#define __MESH_IMPORTER_H__

#include "Application.h"
#include "Module.h"



class MeshImporter : public Module
{

public:
	MeshImporter(Application* app, bool start_enabled = true);
	~MeshImporter();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	void GenerateMesh(const char* path, uint tex = 0);
	string GetName(const char* path);

public:

	bool active = true;

	uint texture = 0;
	uint checker_texture = 0;

};

#endif