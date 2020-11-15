#include "PanelInspector.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"
#include "Component.h"
#include "GameObject.h"
#include "ModuleCamera3D.h"


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

			GameObject* go = App->scene_intro->GOselected;

			if (go != nullptr)
			{
				ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue;
				activeGO = go->data.active;

				ImGui::Spacing();

				ImGui::Checkbox("Active", &activeGO);
				ImGui::SameLine();
				ImGui::InputText(" ", (char*)go->data.name.c_str(), 25, flags);

				ImGui::Spacing();

				/*for (std::vector<Component*>::iterator it = App->scene_intro->GOroot->componentsList.begin(); it != App->scene_intro->GOroot->componentsList.end(); it++)
				{
					(*it)->Save(go->data.id, App->jsonImp);
				}*/

				if (go->data.active && go->GOparent != nullptr)
				{
					for (int i = 0; i < go->componentsList.size(); ++i)
					{
						if (go->componentsList[i] != nullptr)
						{
							go->componentsList[i]->Draw();
							go->componentsList[i]->Update();
							//go->componentsList[i]->Save(go->data.id, App->jsonImp); // Not working
						}
					}
				}

				if (activeGO)
					go->EnableGameObject();
				else
					go->DisableGameObject();
			}

		}

		ImGui::End();
	}

	return true;
}