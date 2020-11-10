#include "PanelInspector.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"
#include "Component.h"
#include "GameObject.h"
#include "ModuleCamera3D.h"

#include "SDL/include/SDL_opengl.h"
#include "imgui-1.78/imgui_impl_sdl.h"

PanelInspector::PanelInspector() : PanelManager()
{
}

PanelInspector::~PanelInspector()
{
}

bool PanelInspector::Start()
{
	this->active = true;

	return true;
}

bool PanelInspector::Draw()
{
	if (!App->gui->Pinspector->active)
		return false;

	if (App->gui->Pinspector->active)
	{
		if (ImGui::Begin("Inspector", &active))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnInspector = true;
			else App->camera->isOnInspector = false;

			GameObject* obj = App->scene_intro->GOselected;

			if (obj != nullptr)
			{
				ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;

				ImGui::Spacing();

				ImGui::Checkbox("Active", &activeGO);
				ImGui::SameLine();
				ImGui::InputText(" ", (char*)obj->oData.GOname.c_str(), 25, flags);

				if (activeGO)
					obj->EnableGameObject();
				else
					obj->DisableGameObject();

				ImGui::Spacing();

				if (obj->oData.active)
				{
					for (int i = 0; i < obj->componentsList.size(); ++i)
					{
						if (obj->componentsList[i] != nullptr)
						{
							obj->componentsList[i]->Draw();
							obj->componentsList[i]->Update();
						}
					}
				}
			}
		}

		ImGui::End();
	}

	return true;
}