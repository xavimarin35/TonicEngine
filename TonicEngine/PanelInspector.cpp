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
			GameObject* obj = App->scene_intro->GOselected;

			if (obj != nullptr)
			{
				ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;

				ImGui::Spacing();

				ImGui::Checkbox("Active", &obj->oData.active); ImGui::SameLine();
				ImGui::InputText(" ", (char*)obj->oData.GOname.c_str(), 25, flags);

				ImGui::Spacing();

				if (obj->oData.active)
				{
					for (std::vector<Component*>::iterator it = obj->componentsList.begin(); it != obj->componentsList.end(); ++it)
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