#include "PanelScene.h"
#include "ModuleCamera3D.h"

PanelScene::PanelScene()
{
}

PanelScene::~PanelScene()
{
}

bool PanelScene::Start()
{
	this->active = true;

	return true;
}

bool PanelScene::Draw()
{
	if (!App->gui->Pscene->active)
		return false;

	if (App->gui->Pscene->active)
	{
		if (ImGui::Begin("Scene", &active))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnScene = true;
			else App->camera->isOnScene = false;
		}






		ImGui::End();
	}

	return true;
}
