#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include "Application.h"
#include "Module.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"

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

	bool enabled = true;

};

#endif