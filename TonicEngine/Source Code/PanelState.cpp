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

			static char* button1 = "Play";
			static char* button2 = "Pause";
			ENGINE_STATE engine_state = App->GetEngineState();

			if (ImGui::ImageButton((ImTextureID*)move.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
				App->gui->currentOp = 1;

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)rot.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
				App->gui->currentOp = 2;

			ImGui::SameLine();

			if (ImGui::ImageButton((ImTextureID*)scale.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)))
				App->gui->currentOp = 3;

			ImGui::SameLine(250);

			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
			if (ImGui::Button(button1, ImVec2(70.0f, 20.0f)))
			{
				button1 = "Stop";
			}
			ImGui::PopStyleColor();
			ImGui::SameLine();
			if (ImGui::Button(button2, ImVec2(70.0f, 20.0f)))
			{

			}
			ImGui::SameLine();

			//Example Color buttons with respective flags
			for (int i = 0; i < 2; i++)
			{
				if (i > 0)
					ImGui::SameLine();
				ImGui::PushID(i);
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
				ImGui::Button("Click");
				ImGui::PopStyleColor(3);
				ImGui::PopID();
			}
		}

		ImGui::End();
	}
	
	return true;
}
