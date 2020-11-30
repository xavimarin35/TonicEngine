#include "PanelState.h"
#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleSceneIntro.h"

PanelState::PanelState()
{
}

PanelState::~PanelState()
{
}

bool PanelState::Start()
{
	this->active = true;

	move = App->tex_imp->LoadTexture("Assets/Others/move2.png");
	rot = App->tex_imp->LoadTexture("Assets/Others/rotate2.png");
	scale = App->tex_imp->LoadTexture("Assets/Others/scale2.png");

	play = App->tex_imp->LoadTexture("Assets/Others/play.png");
	pause = App->tex_imp->LoadTexture("Assets/Others/pause.png");
	stop = App->tex_imp->LoadTexture("Assets/Others/stop.png");
	resume = App->tex_imp->LoadTexture("Assets/Others/resume.png");

	ownBB = App->tex_imp->LoadTexture("Assets/Others/ownBB.png");
	allBB = App->tex_imp->LoadTexture("Assets/Others/allBB.png");

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
			if (ImGui::ImageButton((ImTextureID*)current_tex1.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
			{
				if (currentBut1 == 2) // button texture change play/stop
					currentBut1 = 1;
				else
					currentBut1 = 2;

				if (state == ENGINE_STATE::NONE)
				{
					if (App->PlayScene())
					{
						current_tex1 = pause;
						editing = false;
						LOG_C("Running scene");
					}
				}
				else
				{
					App->StopScene();
					current_tex1 = play;
					editing = true;
					LOG_C("Stopped scene");
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
					ToolTipShortCut("Pause");
				else if (currentBut2 == 4)
					ToolTipShortCut("Resume");
			}

			if (!editing)
				openTimeMenu = true;
			else
				openTimeMenu = false;

		}

		ImGui::End();
	}
	
	return true;
}

void PanelState::DrawGuizmoButtons()
{
	// Move Button
	if (ImGui::ImageButton((ImTextureID*)move.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		App->gui->currentOp = 1;

	if (ImGui::IsItemHovered())
		ToolTipShortCut("Move");

	ImGui::SameLine();

	// Rot Button
	if (ImGui::ImageButton((ImTextureID*)rot.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		App->gui->currentOp = 2;

	if (ImGui::IsItemHovered())
		ToolTipShortCut("Rotate");

	ImGui::SameLine();

	// Scale Button
	if (ImGui::ImageButton((ImTextureID*)scale.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)) || App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
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
	if (ImGui::ImageButton((ImTextureID*)ownBB.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
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
	if (ImGui::ImageButton((ImTextureID*)allBB.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
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
		play_time += App->GetDT();
		current_dt = App->GetDT();

		ImGui::Text("Time Playing: ");	ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, "%.3f", play_time);

		ImGui::Text("Delta Time: ");	ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, "%.3f", current_dt);
	}

	ImGui::End();

}

void PanelState::ToolTipShortCut(const char* word)
{
	ImGui::BeginTooltip();
	ImGui::TextColored(GREY_COLOR, word);
	ImGui::EndTooltip();
}



