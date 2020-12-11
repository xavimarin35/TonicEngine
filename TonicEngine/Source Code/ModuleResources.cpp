#include "Application.h"
#include "ModuleResources.h"
#include "ModuleFileSystem.h"
#include "ModuleGUI.h"
#include "TextureImporter.h"
#include "MeshImporter.h"
#include "ModuleSceneIntro.h"

// resources includes
#include "ModuleResources.h"
#include "Resource.h"
#include "ResourceMesh.h"
#include "ResourceTexture.h"
#include "ResourceModel.h"
#include "ResourceScene.h"

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

	case RESOURCE_TYPE::SCENE:
		ret = (Resource*) new ResourceScene(uid);
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
	else if (CompareExtensionForScenes(extension))
	{
		path = ASSETS_SCENES_FOLDER + path;

		if (App->file_system->CopyFromOutsideFS(new_file, path.c_str()))
		{
		ret = ImportFile(path.c_str(), RESOURCE_TYPE::SCENE);
		}
	}

	return ret;
}

uint ModuleResources::ImportFile(const char* new_file_in_assets, RESOURCE_TYPE type)
{
	uint ret = 0; 
	bool create_resource = false; 
	std::string written_file;
	std::string scene_name;

	ret = GetResourceInAssets(new_file_in_assets);

	if (ret == 0)
	{
		switch (type)
		{
		case RESOURCE_TYPE::TEXTURE: 
			create_resource = App->tex_imp->LoadTextureFromPath(new_file_in_assets, written_file);
			break;
		case RESOURCE_TYPE::MESH:
			break;
		case RESOURCE_TYPE::SCENE:
			break;
		case RESOURCE_TYPE::MODEL:
			break;
		}

		if (create_resource)
		{ 
			Resource* res = CreateResource(type);
			BuildResource(res, new_file_in_assets, written_file);

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

bool ModuleResources::CompareExtensionForScenes(std::string var)
{
	if (var == "json" || var == "JSON")
		return true;
	else
		return false;
}

bool ModuleResources::CompareExtensionForTextures(std::string var)
{
	if (var == "png" || var == "PNG" || var == "dds" || var == "DDS" || var == "jpg" || var == "tga" || var == "ico" || var == "ttex")
		return true;
	else
		return false;
}

void ModuleResources::DrawResources(RESOURCE_TYPE type)
{
	if (type == RESOURCE_TYPE::TEXTURE)
	{
		int i = 0;

		for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
		{
			if (it->second != nullptr && it->second->references > 0)
			{
				if (it->second->type == RESOURCE_TYPE::TEXTURE)
				{
					i++;

					std::map<uint, ResourceTexture*>::const_iterator tex = tex_resources.find(it->first);
					ImGui::ImageButton((ImTextureID*)tex_resources[it->first]->tex.id, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));

					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text("Name:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", App->GetPathName(it->second->file).c_str());
						ImGui::Text("UUID:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%u", it->second->res_UUID);
						ImGui::Text("References:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%i", it->second->references);
						ImGui::EndTooltip();
					}

					AlignResources(i);
				}
			}
		}
	}

	else if (type == RESOURCE_TYPE::MESH)
	{
		int i = 0;

		for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
		{
			if (it->second != nullptr && it->second->references > 0)
			{
				if (it->second->type == RESOURCE_TYPE::MESH)
				{
					i++;

					std::map<uint, ResourceMesh*>::const_iterator mesh = mesh_resources.find(it->first);
					ImGui::ImageButton((ImTextureID*)App->gui->Presources->mesh->tex.id, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));

					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text("Name:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", App->GetPathName(it->second->exported_file).c_str());
						ImGui::Text("Source File:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", App->GetPathName(it->second->file).c_str());
						ImGui::Text("UUID:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%u", it->second->res_UUID);
						ImGui::Text("References:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%i", it->second->references);
						ImGui::EndTooltip();
					}

					AlignResources(i);
				}
			}
		}
	}

	else if (type == RESOURCE_TYPE::MODEL)
	{
		int i = 0;

		for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
		{
			if (it->second != nullptr && it->second->references > 0)
			{
				if (it->second->type == RESOURCE_TYPE::MODEL)
				{
					i++;

					std::map<uint, ResourceModel*>::const_iterator model = model_resources.find(it->first);
					ImGui::ImageButton((ImTextureID*)App->gui->Presources->model->tex.id, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));

					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text("Name:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", App->GetPathName(it->second->exported_file).c_str());
						ImGui::EndTooltip();
					}

					AlignResources(i);
				}
			}
		}
	}

	else if (type == RESOURCE_TYPE::SCENE)
	{
		int i = 0;

		for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
		{
			if (it->second != nullptr && it->second->references > 0)
			{
				if (it->second->type == RESOURCE_TYPE::SCENE)
				{
					i++;

					vector<string> file_list, dir_list;
					std::string name, path;
					App->file_system->DiscoverFiles("Assets/Scenes/", file_list, dir_list);

					for (vector<string>::iterator iterator = file_list.begin(); iterator != file_list.end(); iterator++)
					{
						std::map<uint, ResourceScene*>::const_iterator scene = scene_resources.find(it->first);
						ImGui::ImageButton((ImTextureID*)App->gui->Presources->scene->tex.id, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));
						name = (*iterator).c_str();
						path = ASSETS_SCENES_FOLDER + name;
					}

					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text("Name:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", name.c_str());
						ImGui::Text("Path:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", path.c_str());
						ImGui::EndTooltip();
					}

					AlignResources(i);
				}
			}
		}
	}
}

void ModuleResources::AlignResources(int &i)
{
	if (i < 6)
	{
		ImGui::SameLine();
		ImGui::Dummy(ImVec2(5.0f, 5.0f));
		ImGui::SameLine();
	}
	else
	{
		i = 0;
		ImGui::Dummy(ImVec2(10.0f, 10.0f));
	}
}
