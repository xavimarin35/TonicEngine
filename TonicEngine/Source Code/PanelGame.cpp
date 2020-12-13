#include "PanelGame.h"
#include "ModuleCamera3D.h"

PanelGame::PanelGame()
{
}

PanelGame::~PanelGame()
{
}

bool PanelGame::Start()
{
	this->active = false;

	return true;
}

bool PanelGame::Draw()
{
	if (!App->gui->Pgame->active)
		return false;

	if (App->gui->Pgame->active)
	{
		if (ImGui::Begin("Game", &active))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnGame = true;
			else App->camera->isOnGame = false;
		}

		ImGui::End();
	}

	return true;
}
