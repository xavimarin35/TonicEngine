#include "Application.h"
#include "ModuleResources.h"
#include "ModuleFileSystem.h"

// resources includes
#include "Resource.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ResourceModel.h"

#include <string>

ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Start()
{
	return true;
}

update_status ModuleResources::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleResources::CleanUp()
{
	return true;
}

Resource* ModuleResources::CreateResource(RESOURCE_TYPE type)
{
	Resource* ret = nullptr;

	uint uid = 0; // only for compile purposes, we must call function to create the uid

	switch (type)
	{
	case RESOURCE_TYPE::MESH:
		ret = (Resource*) new ResourceMesh(uid);
		break;

	case RESOURCE_TYPE::TEXTURE:
		ret = (Resource*) new ResourceTexture(uid);
		break;

	case RESOURCE_TYPE::MODEL:
		ret = (Resource*) new ResourceModel(uid);
		break;
	}

	if (ret != nullptr)
		resources[uid] = ret;

	return ret;
}

uint ModuleResources::GetNewFile(const char* new_file)
{
	uint ret = 0;

	std::string path, extension;
	App->file_system->SplitFilePath(new_file, nullptr, &path, &extension);

	if (CompareExtensionForTextures(extension))
	{
		path = ASSETS_TEXTURES_FOLDER + path;

		if (App->file_system->CopyFromOutsideFS(new_file, path.c_str()))
		{
			ret = ImportFile(path.c_str(), RESOURCE_TYPE::TEXTURE);
		}
	}
	else if (CompareExtensionForModels(extension))
	{
		path = ASSETS_MODELS_FOLDER + path;

		if (App->file_system->CopyFromOutsideFS(new_file, path.c_str()))
		{
			ret = ImportFile(path.c_str(), RESOURCE_TYPE::MODEL);
		}
	}

	return ret;
}

uint ModuleResources::ImportFile(const char* new_file_in_assets, RESOURCE_TYPE type)
{
	return uint();
}

Resource* ModuleResources::Get(uint uid)
{
	std::map<uint, Resource*>::iterator it = resources.find(uid);

	if (it != resources.end())
		return it->second;

	return nullptr;
}

bool ModuleResources::CompareExtensionForModels(std::string var)
{
	if (var == "FBX" || var == "fbx" || var == "OBJ" || var == "obj")
		return true;
	else
		return false;
}

bool ModuleResources::CompareExtensionForTextures(std::string var)
{
	if (var == "png" || var == "PNG" || var == "dds" || var == "DDS" || var == "jpg" || var == "tga")
		return true;
	else
		return false;
}

void ModuleResources::DrawResources()
{
}