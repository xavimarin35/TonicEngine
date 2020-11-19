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

			ENGINE_STATE state = App->GetEngineState();
			
			// Button1 manager
			switch (currentBut1)
			{
			case 1: 
				current_tex1 = play;
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Play");
					ImGui::EndTooltip();
				}
				break;
			case 2:
				current_tex1 = stop;
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Stop");
					ImGui::EndTooltip();
				}
				break;
			}

			// Button2 manager
			switch (currentBut2)
			{
			case 3:
				current_tex2 = pause;
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Pause");
					ImGui::EndTooltip();
				}
				break;
			case 4:
				current_tex2 = resume;
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Resume");
					ImGui::EndTooltip();
				}
				break;
			}


			if (ImGui::ImageButton((ImTextureID*)move.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				App->gui->currentOp = 1;

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextColored(GREY_COLOR, "Move");
				ImGui::EndTooltip();
			}

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)rot.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
				App->gui->currentOp = 2;

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextColored(GREY_COLOR, "Rotate");
				ImGui::EndTooltip();
			}

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)scale.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
				App->gui->currentOp = 3;

			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextColored(GREY_COLOR, "Scale");
				ImGui::EndTooltip();
			}

			ImGui::SameLine(250);

			if (ImGui::ImageButton((ImTextureID*)current_tex1.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
			{
				if (currentBut1 == 2) // button texture change play/stop
					currentBut1 = 1;
				else 
					currentBut1 = 2;

				editing = false;

			}

			// Tooltips Button1
			if (ImGui::IsItemHovered())
			{
				if (currentBut1 == 1)
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Play");
					ImGui::EndTooltip();
				}
				else if (currentBut1 == 2)
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Stop");
					ImGui::EndTooltip();
				}
			}

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)current_tex2.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
			{
				if (currentBut2 == 4) // button texture change pause/resume
					currentBut2 = 3;
				else
					currentBut2 = 4;

				if (state == ENGINE_STATE::PLAY)
					current_tex2 = resume;
				else if (state == ENGINE_STATE::PAUSE)
					current_tex2 = pause;

				App->PauseScene();
				LOG_C("Paused scene");
			}

			// Tooltips Button2
			if (ImGui::IsItemHovered())
			{
				if (currentBut2 == 3)
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Pause");
					ImGui::EndTooltip();
				}
				else if (currentBut2 == 4)
				{
					ImGui::BeginTooltip();
					ImGui::TextColored(GREY_COLOR, "Resume");
					ImGui::EndTooltip();
				}
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


