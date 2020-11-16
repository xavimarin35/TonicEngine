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

	return true;
}

bool PanelState::Draw()
{
	if (!App->gui->Pstate->active)
		return false;

	if (App->gui->Pstate->active)
	{
		if (ImGui::Begin("Engine State", &active, ImGuiWindowFlags_NoScrollbar))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnState = true;
			else App->camera->isOnState = false;

			static char* button1 = "Play";
			static char* button2 = "Pause";
			ENGINE_STATE engine_state = App->GetEngineState();

			if (ImGui::Button(button1, ImVec2(70.0f, 20.0f)))
			{
				button1 = "Stop";
			}
			ImGui::SameLine();
			if (ImGui::Button(button2, ImVec2(70.0f, 20.0f)))
			{

			}
		}

		ImGui::End();
	}
	
	return true;
}
