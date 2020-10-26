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
		if (ImGui::Begin("Hierarchy", &active))
		{
			for (std::vector<GameObject*>::iterator it = App->scene_intro->gameobjectsList.begin(); it != App->scene_intro->gameobjectsList.end(); it++)
			{

				if (ImGui::Selectable((*it)->oData.GOname.c_str(), (*it)->oData.active = false))
				{

				}

			}


		}

		ImGui::End();
	}

	return true;
}