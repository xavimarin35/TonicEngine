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


	Resource* CreateResource(RESOURCE_TYPE type);
	uint GetNewFile(const char* new_file);
	uint ImportFile(const char* new_file_in_assets, RESOURCE_TYPE type);

	uint Find(const char* file_in_assets) const;

	uint GenerateNewUID(); 

	Resource* Get(uint uid);


	void DrawExplorer();

private:
	std::map<uint, Resource*> resources;
};

#endif
