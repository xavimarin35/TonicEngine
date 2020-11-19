#include "PanelState.h"
#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleCamera3D.h"

PanelState::PanelState()
{
}

PanelState::~PanelState()
{
}

bool PanelState::Start()
{
	this->active = true;

	move = App->tex_imp->LoadTexture("Assets/Others/move.png");
	rot = App->tex_imp->LoadTexture("Assets/Others/rotate.png");
	scale = App->tex_imp->LoadTexture("Assets/Others/scale.png");
	play = App->tex_imp->LoadTexture("Assets/Others/play.png");
	pause = App->tex_imp->LoadTexture("Assets/Others/pause.png");
	stop = App->tex_imp->LoadTexture("Assets/Others/stop.png");
	resume = App->tex_imp->LoadTexture("Assets/Others/resume.png");

	return true;
}

bool PanelState::CleanUp()
{
	glDeleteTextures(1, (GLuint*)&move);
	glDeleteTextures(1, (GLuint*)&rot);
	glDeleteTextures(1, (GLuint*)&scale);
	glDeleteTextures(1, (GLuint*)&play);
	glDeleteTextures(1, (GLuint*)&pause);
	glDeleteTextures(1, (GLuint*)&stop);
	glDeleteTextures(1, (GLuint*)&resume);

	return true;
}

bool PanelState::Draw()
{
	if (!App->gui->Pstate->active)
		return false;

	if (App->gui->Pstate->active)
	{
		if (ImGui::Begin("Management", &active, ImGuiWindowFlags_NoTitleBar && ImGuiWindowFlags_NoScrollbar && ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnState = true;
			else App->camera->isOnState = false;

			ENGINE_STATE engine_state = App->GetEngineState();

			if (ImGui::ImageButton((ImTextureID*)move.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				App->gui->currentOp = 1;

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)rot.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
				App->gui->currentOp = 2;

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)scale.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
				App->gui->currentOp = 3;

			ImGui::SameLine(250);



			ImGui::SameLine();


		}

		ImGui::End();
	}
	
	return true;
}


