#include "PanelGame.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"

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

		ImVec2 newSize = ImGui::GetWindowContentRegionMax();

	if (newSize.x != size.x || newSize.y != size.y)
	{	
		size = newSize;
		resizedLastFrame = true;
	}

	if (App->camera->GetActiveCamera() != nullptr)
	{
		float AR = App->camera->activeCam->frustum.AspectRatio();

		if (AR != lastAR)
		{
			lastAR = AR;
			resizedLastFrame = true;
		}

		if (resizedLastFrame)
		{
			resizedLastFrame = false;

			viewSize.x = size.x;
			viewSize.y = viewSize.x / AR;

			if (viewSize.y > size.y)
			{
				viewSize.y = size.y;
				viewSize.x = viewSize.y*AR;
			}
		}

		ImGui::SetCursorPos({ (size.x - viewSize.x) / 2, (size.y - viewSize.y) / 2 });
		ImGui::Image((ImTextureID)App->renderer3D->game_tex, { (float)viewSize.x, (float)viewSize.y }, { 0,1 }, { 1,0 });
	}

		ImGui::End();
	}

	return true;
}
