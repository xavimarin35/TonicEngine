#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include "Application.h"
#include "Module.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"

struct MeshObj
{
	uint id_index = 0;
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0;
	uint num_vertex = 0;
	float3* vertex = nullptr;

	uint id_text_coords = 0;
	uint num_text_coords = 0;
	float* text_coords = nullptr;

	uint texture = 0;
};

class ModuleImporter : public Module
{

public:
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Init();

	update_status Update(float dt);

	bool CleanUp();

	void Load(const char* Filename);


public:

	std::vector<MeshObj*> meshes;
	bool enabled = true;

};

#endif