#include "PanelScene.h"
#include "ModuleCamera3D.h"
#include "Viewport.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

PanelScene::PanelScene()
{
}

PanelScene::~PanelScene()
{
}

// EVERYTHING COMMENTED IS WORK IN PROGRESS

bool PanelScene::Start()
{
	this->active = false;

	//viewport_tex = new Viewport();
	//viewport_tex->StartBuffers(current_size);

	return true;
}

bool PanelScene::Draw()
{
	if (!App->gui->Pscene->active)
		return false;

	if (App->gui->Pscene->active)
	{
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

		if (ImGui::Begin("Scene", &active))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnScene = true;
			else App->camera->isOnScene = false;
		}

		/*ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();

		vMin.x += ImGui::GetWindowPos().x;
		vMin.y += ImGui::GetWindowPos().y;
		vMax.x += ImGui::GetWindowPos().x;
		vMax.y += ImGui::GetWindowPos().y;

		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));

		new_size = ImGui::GetContentRegionAvail();

		ImGui::Image((ImTextureID)viewport_tex->texture, ImVec2(current_size.x, current_size.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();*/
	}

	return true;
}


update_status PanelScene::PreUpdate(float dt)
{
	/*if (current_size.x != new_size.x || current_size.y != new_size.y)
	{
		current_size = new_size;
		viewport_tex->StartBuffers(current_size);
		App->renderer3D->OnResize(current_size.x, current_size.y);
	}

	viewport_tex->BindViewport();*/

	return UPDATE_CONTINUE;
}

update_status PanelScene::PostUpdate(float dt)
{
	//viewport_tex->UnbindViewport();

	return UPDATE_CONTINUE;
}

bool PanelScene::CleanUp()
{
	/*viewport_tex->DeleteBuffers();
	delete viewport_tex;
	viewport_tex = nullptr;*/

	return true;
}