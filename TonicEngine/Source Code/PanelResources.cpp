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

	return true;
}

bool PanelResources::Draw()
{
	if (!App->gui->Presources->active)
		return false;

	if (App->gui->Presources->active)
	{
		if (ImGui::Begin("Resources", &active, ImGuiWindowFlags_NoDecoration))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnResources = true;
			else App->camera->isOnResources = false;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_AlwaysAutoResize;

			ImGui::BeginChild("Resources Tree", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.20f, 260), false, window_flags);
			

			// Dont zoom in/out when this child window is hovered
			if (ImGui::IsWindowHovered()) App->camera->isOnResources = true;
			else App->camera->isOnResources = false;

			if (ImGui::TreeNodeEx("Project", ImGuiTreeNodeFlags_DefaultOpen))
			{
				if (ImGui::TreeNodeEx("Library", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Image((ImTextureID)folder->tex.id, ImVec2(15, 15), ImVec2(0, 1), ImVec2(1, 0));
					ImGui::SameLine();
					ImGui::Selectable("Meshes", &showing_meshes);

					ImGui::Image((ImTextureID)folder->tex.id, ImVec2(15, 15), ImVec2(0, 1), ImVec2(1, 0));
					ImGui::SameLine();
					ImGui::Selectable("Textures", &showing_textures);
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}


			/*if (showing_meshes)
			{
				showing_textures = false;
				showing_meshes = true;
			}

			if (showing_textures)
			{
				showing_meshes = false;
				showing_textures = true;
			}*/
			

			ImGui::EndChild();


			ImGui::SameLine();

			ImGuiWindowFlags window_flags2 = ImGuiWindowFlags_AlwaysAutoResize;
 
			ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
			ImGui::BeginChild("Resources Icons", ImVec2(0, 260), true, window_flags2);

			// Dont zoom in/out when this child window is hovered
			if (ImGui::IsWindowHovered()) App->camera->isOnResources = true;
			else App->camera->isOnResources = false;

			if (showing_meshes)
				App->resources->DrawResources(RESOURCE_TYPE::MESH);

			if (showing_textures)
				App->resources->DrawResources(RESOURCE_TYPE::TEXTURE);

			ImGui::EndChild();
			ImGui::PopStyleVar();


			//if (ImGui::Button("Meshes"))
			//{
			//	showing_textures = false;
			//	showing_meshes = true;
			//}

			//if (ImGui::Button("Textures"))
			//{
			//	showing_meshes = false;
			//	showing_textures = true;
			//}

			
		}

		ImGui::End();
	}

	return true;
}