#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include "Application.h"
#include "Module.h"

#include <vector>

class MeshObj;

class ModuleImporter : public Module
{

public:
	ModuleImporter(Application* app, bool start_enabled = true);
	~ModuleImporter();

	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	bool Draw();

	bool CleanUp();

	bool Load(const char* Filename);


private:

	std::vector<MeshObj*> meshes;
	bool enabled;

};

#endif