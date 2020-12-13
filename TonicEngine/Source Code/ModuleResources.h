#ifndef __ModuleResources_H__
#define __ModuleResources_H__

#include "Application.h"
#include "Module.h"
#include "Resource.h"
#include "PanelConsole.h"

struct Assets
{
	enum FOLDERS
	{
		ASSETS,
		LIBRARY
	}folders;

	enum TYPE
	{
		FOLDER, 
		FILE
	}type;

	std::string name = "";
};


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
	void AlignResources(int &i);

	Resource* CreateResource(RESOURCE_TYPE type);
	Resource* BuildResource(Resource* res, const char* file, std::string written);
	uint GetNewFile(const char* new_file);
	uint ImportFile(const char* new_file_in_assets, RESOURCE_TYPE type);

	Resource* Get(uint uid);

	uint GetResourceFromFolder(Assets::FOLDERS folder, const char* path);
	void ClearAssets();

	bool CompareExtensionForTextures(std::string var);
	bool CompareExtensionForModels(std::string var);
	bool CompareExtensionForScenes(std::string var);

public: 

	std::map<uint, Resource*> resources;
	std::map<uint, ResourceTexture*> tex_resources;
	std::map<uint, ResourceMesh*> mesh_resources;

	std::list<Assets*> assets;
	std::string models_path = ASSETS_MODELS_FOLDER;

private:

	bool isTexture = false;

	std::string text_path;
	
};

#endif
