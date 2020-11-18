#include "PanelResources.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"

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

		}

		ImGui::End();
	}

	return true;
}