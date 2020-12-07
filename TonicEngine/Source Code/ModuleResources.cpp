#include "Application.h"
#include "ModuleResources.h"
#include "ModuleFileSystem.h"
#include "ModuleGUI.h"
#include "TextureImporter.h"
#include "MeshImporter.h"

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

	uint uid = App->GenerateUUID();

	switch (type)
	{
	case RESOURCE_TYPE::MESH:
		ret = (Resource*) new ResourceMesh(uid);
		break;

	case RESOURCE_TYPE::TEXTURE:
		ret = (Resource*) new ResourceTexture(uid);
		if (ret != nullptr)
			tex_resources[uid] = (ResourceTexture*)ret;
		break;

	case RESOURCE_TYPE::MODEL:
		ret = (Resource*) new ResourceModel(uid);
		break;
	}

	if (ret != nullptr)
		resources[uid] = ret;

	return ret;
}

Resource* ModuleResources::BuildResource(Resource* res, const char* file, std::string written)
{
	res->file = file;
	res->exported_file = written;

	return res;
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
	uint ret = 0; 
	bool create_resource = false; 
	std::string written_file;

	ret = GetResourceInAssets(new_file_in_assets);

	if (ret == 0)
	{
		switch (type)
		{
		case RESOURCE_TYPE::TEXTURE: 
			create_resource = App->tex_imp->LoadTextureFromPath(new_file_in_assets, written_file);
			break;
		}

		if (create_resource)
		{ 

			Resource* res = CreateResource(type);
			res->file = new_file_in_assets;
			res->exported_file = written_file;
			//BuildResource(res, new_file_in_assets, written_file);

			ret = res->res_UUID;
		}
	}

	return ret;
}

Resource* ModuleResources::Get(uint uid)
{
	std::map<uint, Resource*>::iterator it = resources.find(uid);

	if (it != resources.end())
		return it->second;

	return nullptr;
}

uint ModuleResources::GetResourceInAssets(const char* path) const
{
	for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
	{
		std::string s = it->second->file;
		if (s.compare(path) == 0)
			return it->first;
	}

	return 0;
}

uint ModuleResources::IsResourceInLibrary(const char* name) const
{
	for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
	{
		char n[250];
		sprintf_s(n, 250, "%s", name);
		App->file_system->NormalizePath(n);

		std::string s = App->GetPathName(it->second->exported_file);

		if (s.compare(n) == 0)
			return it->first;
	}

	return 0;
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
	if (var == "png" || var == "PNG" || var == "dds" || var == "DDS" || var == "jpg" || var == "tga" || var == "ico")
		return true;
	else
		return false;
}

void ModuleResources::DrawResources()
{
	int i = 0;

	for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
	{
		if (it->second != nullptr)
		{
			i++;
			if (it->second->type == RESOURCE_TYPE::TEXTURE)
			{
					std::map<uint, ResourceTexture*>::const_iterator tex = tex_resources.find(it->first);
					ImGui::ImageButton((ImTextureID*)tex_resources[it->first]->tex.id, ImVec2(50, 50), ImVec2(0, 1), ImVec2(1, 0));

					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Name: %s\nUUID: %u", App->GetPathName(it->second->file).c_str(), it->second->res_UUID);
			}

			if (i < 8)
			{
				ImGui::SameLine();
				ImGui::Dummy(ImVec2(5.0f, 5.0f));
				ImGui::SameLine();

			}
			else
			{
				i = 0;
				ImGui::Dummy(ImVec2(875.0f, 10.0f));
			}
		}
	}
}