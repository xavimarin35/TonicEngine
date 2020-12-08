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

	void DrawResources(RESOURCE_TYPE type);

	Resource* CreateResource(RESOURCE_TYPE type);
	Resource* BuildResource(Resource* res, const char* file, std::string written);
	uint GetNewFile(const char* new_file);
	uint ImportFile(const char* new_file_in_assets, RESOURCE_TYPE type);

	Resource* Get(uint uid);
	uint GetResourceInAssets(const char* path) const;
	uint IsResourceInLibrary(const char* name) const;

	bool CompareExtensionForTextures(std::string var);
	bool CompareExtensionForModels(std::string var);

	std::map<uint, Resource*> resources;
	std::map<uint, ResourceTexture*> tex_resources;
	std::map<uint, ResourceMesh*> mesh_resources;

private:
	
};

#endif
