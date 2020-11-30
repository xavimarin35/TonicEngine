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