#include "PanelManagement.h"
#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleCamera3D.h"

PanelManagement::PanelManagement()
{
}

PanelManagement::~PanelManagement()
{
}

bool PanelManagement::Start()
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

bool PanelManagement::CleanUp()
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

bool PanelManagement::Draw()
{
	if (!App->gui->Pmanagement->active)
		return false;

	if (App->gui->Pmanagement->active)
	{
		if (ImGui::Begin("Management", &active, ImGuiWindowFlags_NoTitleBar && ImGuiWindowFlags_NoScrollbar && ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnState = true;
			else App->camera->isOnState = false;

			state = App->GetEngineState();
			current_tex1 = play;
			current_tex2 = pause;

			if (ImGui::ImageButton((ImTextureID*)move.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				App->gui->currentOp = 1;

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)rot.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
				App->gui->currentOp = 2;

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)scale.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
				App->gui->currentOp = 3;

			ImGui::SameLine(250);

			if (ImGui::ImageButton((ImTextureID*)current_tex1.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
			{
					current_tex1 = pause;
					editing = false;
					LOG_C("Running scene");
			
			}

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)current_tex2.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
			{
				if (state == ENGINE_STATE::PLAY)
					current_tex2 = resume;
				else if (state == ENGINE_STATE::PAUSE)
					current_tex2 = pause;

				App->PauseScene();
				LOG_C("Paused scene");
			}

			if (!editing)
			{
				// show the current time in playmode
				play_time =+ App->GetDT(); ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%.2f", play_time);
			}
		}

		ImGui::End();
	}
	
	return true;
}


