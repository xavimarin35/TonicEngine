#include "PanelResources.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleResources.h"
#include "ResourceTexture.h"

PanelResources::PanelResources() : PanelManager()
{
}

PanelResources::~PanelResources()
{
}

bool PanelResources::Start()
{
	this->active = true;

	folder = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Library/Textures/folder-icon.dds"));
	folder->LoadInMemory();

	mesh = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/resource_fbx.png"));
	mesh->LoadInMemory();

	return true;
}

bool PanelResources::Draw()
{
	if (!App->gui->Presources->active)
		return false;

	if (App->gui->Presources->active)
	{
		if (ImGui::Begin("Resources", &active, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnResources = true;
			else App->camera->isOnResources = false;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::BeginChild("Resources Tree", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.20f, 260), false, window_flags);

			if (ImGui::IsWindowHovered()) 
				App->camera->isOnResourcesChild1 = true;
			else App->camera->isOnResourcesChild1 = false;

			if (ImGui::TreeNodeEx("Project", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::TreeNodeEx("Assets", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Image((ImTextureID)folder->tex.id, ImVec2(15, 15), ImVec2(0, 1), ImVec2(1, 0));
					ImGui::SameLine();
					ImGui::Selectable("Meshes", &showing_meshes);

					ImGui::Image((ImTextureID)folder->tex.id, ImVec2(15, 15), ImVec2(0, 1), ImVec2(1, 0));
					ImGui::SameLine();
					ImGui::Selectable("Textures", &showing_textures);

					ImGui::Image((ImTextureID)folder->tex.id, ImVec2(15, 15), ImVec2(0, 1), ImVec2(1, 0));
					ImGui::SameLine();
					ImGui::Selectable("Scenes", &showing_scenes);
					
					ImGui::Image((ImTextureID)folder->tex.id, ImVec2(15, 15), ImVec2(0, 1), ImVec2(1, 0));
					ImGui::SameLine();
					ImGui::Selectable("Models", &showing_models);
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}

			ImGui::EndChild();


			ImGui::SameLine();

			ImGuiWindowFlags window_flags2 = ImGuiWindowFlags_AlwaysAutoResize;
 
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::BeginChild("Resources Icons", ImVec2(0, 260), true, window_flags2);

			if (ImGui::IsWindowHovered()) App->camera->isOnResourcesChild2 = true;
			else App->camera->isOnResourcesChild2 = false;

			if (showing_meshes)
				App->resources->DrawResources(RESOURCE_TYPE::MESH);

			if (showing_textures)
				App->resources->DrawResources(RESOURCE_TYPE::TEXTURE);

			if (showing_scenes)
				App->resources->DrawResources(RESOURCE_TYPE::SCENE);

			if (showing_models)
				App->resources->DrawResources(RESOURCE_TYPE::MODEL);

			ImGui::EndChild();
			ImGui::PopStyleVar();

		}

		ImGui::End();
	}

	return true;
}

