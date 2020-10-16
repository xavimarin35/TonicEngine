#include "PanelHierarchy.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"

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
		/*App->window->GetWindowSize(w_width, w_height);
		ImGui::SetNextWindowPos(PANELHIERARCHY_POS, ImGuiCond_Once);
		ImGui::SetNextWindowSize(PANELHIERARCHY_SIZE, ImGuiCond_Once);*/

		if (ImGui::Begin("Hierarchy", &active, ImGuiWindowFlags_AlwaysAutoResize))
		{
			
		}

		ImGui::End();
	}

	return true;
}