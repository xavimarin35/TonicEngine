#include "PanelInspector.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"
#include "Component.h"
#include "GameObject.h"

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
			if (App->scene_intro->GOselected != nullptr)
			{
				ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;

				ImGui::Spacing();

				ImGui::Checkbox("Active", &App->scene_intro->GOselected->oData.active); ImGui::SameLine();
				ImGui::InputText("Name", (char*)App->scene_intro->GOselected->oData.GOname.c_str(), 25, flags);

				ImGui::Spacing();

				if (App->scene_intro->GOselected->oData.active)
				{
					for (std::vector<Component*>::iterator it = App->scene_intro->GOselected->componentsList.begin(); it != App->scene_intro->GOselected->componentsList.end(); ++it)
					{
						if (*it != nullptr)
						{
							(*it)->Draw();
						}
					}
				}
			}
		}

		ImGui::End();
	}

	return true;
}