#include "PanelResources.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "ModuleResources.h"

PanelResources::PanelResources() : PanelManager()
{
}

PanelResources::~PanelResources()
{
}

bool PanelResources::Start()
{
	this->active = true;

	return true;
}

bool PanelResources::Draw()
{
	if (!App->gui->Presources->active)
		return false;

	if (App->gui->Presources->active)
	{
		if (ImGui::Begin("Resources", &active))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnResources = true;
			else App->camera->isOnResources = false;


			if (ImGui::Button("Meshes"))
			{
				showing_textures = false;
				showing_meshes = true;
			}

			if (ImGui::Button("Textures"))
			{
				showing_meshes = false;
				showing_textures = true;
			}

			if (showing_meshes)
				App->resources->DrawResources(RESOURCE_TYPE::MESH);

			if (showing_textures)
				App->resources->DrawResources(RESOURCE_TYPE::TEXTURE);
		}

		ImGui::End();
	}

	return true;
}