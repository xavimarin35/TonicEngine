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

	void LoadMesh(const char* Filename);
	void GenerateMesh(const char* path, uint tex = 0);


public:

	bool enabled = true;

	uint texture;
	uint checker_texture;

};

#endif