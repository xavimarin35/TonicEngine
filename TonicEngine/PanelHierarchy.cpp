#include "PanelHierarchy.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"

#include "SDL/include/SDL_opengl.h"
#include "imgui-1.78/imgui_impl_sdl.h"

PanelHierarchy::PanelHierarchy() : PanelManager()
{
}

PanelHierarchy::~PanelHierarchy()
{
}

bool PanelHierarchy::Start()
{
	this->active = true;

	return true;
}

bool PanelHierarchy::Draw()
{
	if (!App->gui->Phierarchy->active)
		return false;

	if (App->gui->Phierarchy->active)
	{

		if (ImGui::Begin("Hierarchy", &active, ImGuiWindowFlags_NoFocusOnAppearing))
		{
			

			for (uint i = 0; i < App->scene_intro->gameobjectsList.size(); ++i)
			{
				if (ImGui::Selectable(App->scene_intro->gameobjectsList.at(i)->oData.GOname.data(), App->scene_intro->gameobjectsList.at(i)->oData.GOid == i))
				{
					if (ImGui::IsItemActive) 
					{
						App->scene_intro->GOselected = App->scene_intro->gameobjectsList.at(i);
						// ------------------
						App->scene_intro->GOselected->oData.GOid = i; 
						selectedGO = App->scene_intro->gameobjectsList.at(i)->oData.GOid;
					}

					switch (i) 
					{
						case 0:
							LOG_IMGUI_CONSOLE("Selected GameObject i = %i", i);
							break;
						case 1:
							LOG_IMGUI_CONSOLE("Selected GameObject i = %i", i);
							break;
					}
				}
			}	
			
		}

		ImGui::End();
	}

	return true;
}