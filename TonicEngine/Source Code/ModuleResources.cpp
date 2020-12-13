#include "Application.h"
#include "ModuleResources.h"
#include "ModuleFileSystem.h"
#include "ModuleGUI.h"
#include "TextureImporter.h"
#include "MeshImporter.h"
#include "ModuleSceneIntro.h"
#include "PanelResources.h"

// resources includes
#include "ModuleResources.h"
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
	App->file_system->GetFilesOfFolder(ASSETS_MODELS_FOLDER, assets);

	return true;
}

update_status ModuleResources::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleResources::CleanUp()
{
	bool ret = true;

	std::map <uint, Resource*>::iterator it;
	it = resources.begin();
	while (it != resources.end())
	{
		RELEASE((*it).second);
		it++;
	}

	resources.clear();

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

	return ret;
}

uint ModuleResources::ImportFile(const char* new_file_in_assets, RESOURCE_TYPE type)
{
	uint ret = 0; 
	bool create_resource = false; 
	std::string written_file;

	ret = GetResourceFromFolder(Assets::FOLDERS::ASSETS, new_file_in_assets);

	if (ret == 0)
	{
		switch (type)
		{
		case RESOURCE_TYPE::TEXTURE: 
			create_resource = App->tex_imp->LoadTextureFromPath(new_file_in_assets, written_file);
			break;
		case RESOURCE_TYPE::MESH:
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

uint ModuleResources::GetResourceFromFolder(Assets::FOLDERS folder, const char* path)
{
	if (folder == Assets::FOLDERS::ASSETS)
	{
		for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
		{
			std::string s = it->second->file;
			if (s.compare(path) == 0)
				return it->first;
		}

		return 0;
	}

	if (folder == Assets::FOLDERS::LIBRARY)
	{
		for (std::map<uint, Resource*>::const_iterator it = resources.begin(); it != resources.end(); ++it)
		{
			char n[250];
			sprintf_s(n, 250, "%s", path);
			App->file_system->NormalizePath(n);

			std::string s = App->GetPathName(it->second->exported_file);

			if (s.compare(n) == 0)
				return it->first;
		}

		return 0;
	}

	return 0;
}

void ModuleResources::ClearAssets()
{
	std::list<Assets*>::iterator it;
	it = assets.begin();
	while (it != assets.end())
	{
		RELEASE(*it);
		it++;
	}
	assets.clear();
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

		ImGui::Spacing();
		ImGui::TextColored(GREY_COLOR, "You can double-click on a texture to assign it to the selected GameObject");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

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
						if (ImGui::IsMouseDoubleClicked(0))
						{
							GameObject* GO = App->scene_intro->GOselected;

							if (GO == nullptr)
							{
								LOG_C("WARNING: You must select a Game Object to assign a texture to it");
							}

							else if (GO != nullptr)
							{
								if (GO->GetComponentTexture() == nullptr)
								{
									LOG_C("WARNING: This Game Object doesn't have a Component Texture, maybe try with another child");
								}

								else if (GO->GetComponentTexture() != nullptr)
								{
									GO->GetComponentTexture()->rTexture = tex_resources[it->first];
								}
							}
						}

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
				if (it->second->type == RESOURCE_TYPE::MESH && it->second->references > 0)
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
		
		ImGui::Spacing();
		ImGui::TextColored(GREY_COLOR, "You can double-click on a model to load it into the scene");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		
		for (std::list<Assets*>::iterator it = assets.begin(); it != assets.end(); it++)
		{
			// If the file is a texture, don't print it, just get the path
			if ((*it)->type == Assets::TYPE::FILE)
			{
				std::string extension;
				std::string filename;
				App->file_system->SplitFilePath((*it)->name.c_str(), nullptr, &filename, &extension);

				std::string complete_path = "Assets/Models/";
				std::string mesh = "";
				std::string tex = "";

				if ((extension == "png" || extension == "PNG" || extension == "dds" || extension == "DDS"))
				{
					isTexture = true;
					text_path = complete_path + filename;
				}
				else isTexture = false;
			}

			// If the file is not a texture, draw it
			if (!isTexture)
			{
				i++;

				ImGui::ImageButton((ImTextureID)App->gui->Presources->model->tex.id, ImVec2(60, 60), ImVec2(0, 1), ImVec2(1, 0));

				if (ImGui::IsItemHovered())
				{
					if ((*it)->type == Assets::TYPE::FILE)
					{
						std::string extension;
						std::string filename;
						App->file_system->SplitFilePath((*it)->name.c_str(), nullptr, &filename, &extension);

						std::string complete_path = "Assets/Models/";
						std::string mesh = "";
						std::string tex = "";

						if ((extension == "fbx" || extension == "FBX" || extension == "OBJ" || extension == "obj"))
						{
							mesh = complete_path + filename;
						}

						ImGui::BeginTooltip();
						ImGui::Text("Name:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", filename.c_str());
						ImGui::Text("Source File:"); ImGui::SameLine();
						ImGui::TextColored(YELLOW_COLOR, "%s", mesh.c_str());
						ImGui::EndTooltip();

						if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
							App->mesh_imp->LoadFile(mesh, text_path);
					}
				}

				AlignResources(i);
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