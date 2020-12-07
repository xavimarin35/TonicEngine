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

			//App->resources->DrawResources();
		}

		ImGui::End();
	}

	return true;
}