#include "PanelGame.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"

PanelGame::PanelGame()
{
}

PanelGame::~PanelGame()
{
}

bool PanelGame::Start()
{
	this->active = true;

	return true;
}

bool PanelGame::Draw()
{
	if (!App->gui->Pgame->active)
		return false;

	if (App->gui->Pgame->active)
	{
		if (ImGui::Begin("Game", &active, ImGuiWindowFlags_NoScrollbar))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnGame = true;
			else App->camera->isOnGame = false;
		}

		ImVec2 newSize = ImGui::GetWindowSize();
		ImVec2 size = { 0, 0 };
		if (newSize.x != size.x || newSize.y != size.y)
		{
			size = newSize;
			float newAR = size.x / size.y;
			App->camera->playCam->GetComponentCamera()->SetRatio(newAR);
			//App->renderer3D->changedSceneFOV = true;
		}

		ImGui::Image((ImTextureID)App->renderer3D->game_tex, ImVec2((float)newSize.x, (float)newSize.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
	}

	return true;
}
