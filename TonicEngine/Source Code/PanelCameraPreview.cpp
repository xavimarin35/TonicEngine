#include "PanelCameraPreview.h"
#include "Application.h"
#include "ModuleGUI.h"

PanelCameraPreview::PanelCameraPreview()
{
}

PanelCameraPreview::~PanelCameraPreview()
{
}

bool PanelCameraPreview::Start()
{
	this->active = false;

	return true;
}

bool PanelCameraPreview::Draw()
{
	if (!App->gui->Pcam->active)
		return false;

	if (App->gui->Pcam->active)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin("Camera Preview", &active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse))
			//ImGui::Image((ImTextureID)viewport_tex->texture, ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();
	}

	return true;
}

update_status PanelCameraPreview::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status PanelCameraPreview::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool PanelCameraPreview::CleanUp()
{
	return true;
}