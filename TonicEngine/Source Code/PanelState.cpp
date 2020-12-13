#include "PanelState.h"
#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleResources.h"
#include "Resource.h"
#include "ResourceTexture.h"
#include "ResourceMesh.h"
#include "ModuleTime.h"

PanelState::PanelState()
{
}

PanelState::~PanelState()
{
}

bool PanelState::Start()
{
	this->active = true;

	LoadButtonsTextures();

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

	glDeleteTextures(1, (GLuint*)&ownBB);
	glDeleteTextures(1, (GLuint*)&allBB);

	return true;
}

bool PanelState::Draw()
{
	if (!App->gui->Pstate->active)
		return false;

	if (App->gui->Pstate->active)
	{
		if (ImGui::Begin("Options Bar", &active, ImGuiWindowFlags_NoDecoration))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnState = true;
			else App->camera->isOnState = false;

			if (openTimeMenu)
				TimeInfoMenu();

			ENGINE_STATE state = App->GetEngineState();

			ManageEngineStateButtonsLogic();

			DrawGuizmoButtons();

			ImGui::SameLine(180);

			DrawBBButtons();

			ImGui::SameLine(300);

			// Engine State Button 1
			if (ImGui::ImageButton((ImTextureID*)current_tex1->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
			{
				if (!App->camera->playCam->IsGameObjectActive())
				{
					LOG_C("ERROR: Couldn't find any camera.");
					LOG_C("ERROR: Enable it, or create a new one and set it as Game Camera.");
				}
				else
				{
					if (currentBut1 == 2) // button texture change play/stop
						currentBut1 = 1;
					else
						currentBut1 = 2;

					if (state == ENGINE_STATE::NONE)
					{
						if (App->PlayScene())
						{
							current_tex1 = stop;
							editing = false;
						}
					}
					else
					{
						App->StopScene();
						current_tex1 = play;
						editing = true;
					}
				}
			}

			// Tooltips Button1
			if (ImGui::IsItemHovered())
			{
				if (currentBut1 == 1)
					ToolTipShortCut("Play");
				else if (currentBut1 == 2)
					ToolTipShortCut("Stop");
			}

			ImGui::SameLine();

			// Engine State Button 2
			if (ImGui::ImageButton((ImTextureID*)current_tex2->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
			{
				// button texture change pause/resume
				if (currentBut2 == 3 && currentBut1 != 1)
					currentBut2 = 4;
				else
					currentBut2 = 3;

				if (state == ENGINE_STATE::PLAY)
					current_tex2 = resume;
				else if (state == ENGINE_STATE::PAUSE)
					current_tex2 = pause;

				App->PauseScene();
			}

			// Tooltips Button2
			if (ImGui::IsItemHovered())
			{
				if (currentBut2 == 3)
					ToolTipShortCut("Pause");
				else if (currentBut2 == 4)
					ToolTipShortCut("Resume");
			}

			if (!editing)
				openTimeMenu = true;
			else
			{
				openTimeMenu = false;
				currentBut1 = 1;
				currentBut2 = 3;
			}
		}

		ImGui::End();
	}
	
	return true;
}

void PanelState::DrawGuizmoButtons()
{
	// Move Button
	if (ImGui::ImageButton((ImTextureID*)move->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && !App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN))
		App->gui->currentOp = 1;

	if (ImGui::IsItemHovered())
		ToolTipShortCut("Move");

	ImGui::SameLine();

	// Rot Button
	if (ImGui::ImageButton((ImTextureID*)rot->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && !App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN))
		App->gui->currentOp = 2;

	if (ImGui::IsItemHovered())
		ToolTipShortCut("Rotate");

	ImGui::SameLine();

	// Scale Button
	if (ImGui::ImageButton((ImTextureID*)scale->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && (!App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_DOWN && !App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_DOWN)))
		App->gui->currentOp = 3;

	if (ImGui::IsItemHovered())
		ToolTipShortCut("Scale");
}

void PanelState::ManageEngineStateButtonsLogic()
{
	// Button1 manager
	switch (currentBut1)
	{
	case 1:
		current_tex1 = play;
		break;
	case 2:
		current_tex1 = stop;
		break;
	}

	// Button2 manager
	switch (currentBut2)
	{
	case 3:
		current_tex2 = pause;
		break;
	case 4:
		current_tex2 = resume;
		break;
	}
}

void PanelState::DrawBBButtons()
{
	// Own BB
	if (ImGui::ImageButton((ImTextureID*)ownBB->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
	{
		if (App->scene_intro->GOselected != nullptr)
		{
			if (drawBB == 1) drawBB = 0;
			else drawBB = 1;
		}

		else if (App->scene_intro->GOselected == nullptr || !App->scene_intro->GOselected->data.active)
			LOG_C("WARNING: You must active or select a GameObject to use this tool");
	}

	if (ImGui::IsItemHovered())
		ToolTipShortCut("Draw own BB");

	ImGui::SameLine();

	// All BB
	if (ImGui::ImageButton((ImTextureID*)allBB->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
	{
		if (drawBB == 2) drawBB = 0;
		else drawBB = 2;
	}

	if (ImGui::IsItemHovered())
		ToolTipShortCut("Draw all BBs");
}

void PanelState::TimeInfoMenu()
{
	if (ImGui::Begin("Time Information", &openTimeMenu, ImGuiWindowFlags_NoScrollbar))
	{
		play_time = App->time->GetPlayModeCurrentTime();
		current_dt = App->GetDT();

		ImGui::Text("Time Playing: ");	ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, "%.3f", play_time);

		ImGui::Text("Delta Time: ");	ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, "%.3f", current_dt);
	}

	ImGui::End();
}

void PanelState::LoadButtonsTextures()
{
	move = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/move2.png"));
	move->LoadInMemory();
	rot = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/rotate2.png"));
	rot->LoadInMemory();
	scale = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/scale2.png"));
	scale->LoadInMemory();

	play = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/play.png"));
	play->LoadInMemory();
	pause = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/pause.png"));
	pause->LoadInMemory();
	stop = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/stop.png"));
	stop->LoadInMemory();
	resume = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/resume.png"));
	resume->LoadInMemory();

	ownBB = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/ownBB.png"));
	ownBB->LoadInMemory();
	allBB = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/allBB.png"));
	allBB->LoadInMemory();
}

void PanelState::ToolTipShortCut(const char* word)
{
	ImGui::BeginTooltip();
	ImGui::TextColored(GREY_COLOR, word);
	ImGui::EndTooltip();
}