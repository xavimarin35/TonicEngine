#ifndef __ModuleResources_H__
#define __ModuleResources_H__

#include "Application.h"
#include "Module.h"
#include "Resource.h"

class Resource;
class ResourceMesh;
class ResourceTexture;

class ModuleResources : public Module
{
public:

	ModuleResources(Application* app, bool start_enabled = true);
	virtual ~ModuleResources();

	bool Start();
	update_status Update();
	bool CleanUp();

	void DrawResources();

	Resource* CreateResource(RESOURCE_TYPE type);
	uint GetNewFile(const char* new_file);
	uint ImportFile(const char* new_file_in_assets, RESOURCE_TYPE type);

	Resource* Get(uint uid);

	bool CompareExtensionForTextures(std::string var);
	bool CompareExtensionForModels(std::string var);

private:
	std::map<uint, Resource*> resources;
};

#endif
