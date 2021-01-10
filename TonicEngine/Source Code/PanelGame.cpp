#include "PanelGame.h"
#include "ModuleCamera3D.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "MeshImporter.h"

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

			App->gui->gameX = ImGui::GetCursorPosX() + ImGui::GetWindowPos().x;
			App->gui->gameY = ImGui::GetCursorPosY() + ImGui::GetWindowPos().y;
			App->gui->gameW = size.x;
			App->gui->gameH = size.y;

			App->gui->gameMousePos = { ImGui::GetMousePos().x - App->gui->gameX, ImGui::GetMousePos().y - App->gui->gameY };

			if (App->gui->isButton && !continued)
			{
				if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
				{
					continued = true;
					DoButtonFunction(0);
				}
			}			

			if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN && continued)
			{
				ChangeVsync();
			}
		}

		ImGui::End();
	}

	return true;
}

void PanelGame::DoButtonFunction(int function)
{
	if (function == 0)
		LoadStreet();

	else if (function == 1)
		ChangeVsync();
}

void PanelGame::LoadStreet()
{
	App->scene_intro->Create3DObject(OBJECTS3D::STREET);

	for (int i = 0; i < App->scene_intro->gameobjectsList.size(); i++)
	{
		if (App->scene_intro->gameobjectsList[i]->GetComponentImageUI() != nullptr || App->scene_intro->gameobjectsList[i]->GetComponentButtonUI() != nullptr)
		{
			App->scene_intro->gameobjectsList[i]->CleanUp();
		}
	}

	App->camera->GetGameCamera()->GetComponentTransform()->SetPosition(float3(11, 25.5, 82));

	vsyncBut = App->mesh_imp->LoadUI(ELEMENT_UI_TYPE::BUTTON, "Assets/BasicShapes/bUI.fbx", "Assets/Others/vsync_but.png");
	vsyncBut->GetComponentTransform()->SetScale(float3(5, 1, 1));
	vsyncBut->GetComponentTransform()->SetPosition(float3(0.5, -3.5, 0.001));
}

void PanelGame::ChangeVsync()
{
	App->vsyncB = !App->vsyncB;

	if (App->vsyncB) {
		SDL_GL_SetSwapInterval(1);
		LOG_C("VSYNC activated");
	}

	else if (!App->vsyncB) {
		SDL_GL_SetSwapInterval(0);
		LOG_C("VSYNC deactivated");
	}
}