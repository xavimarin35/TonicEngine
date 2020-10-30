#include "PanelHierarchy.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "MeshImporter.h"
#include "ModuleCamera3D.h"

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
			if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
				App->scene_intro->RemoveSelectedGO(App->scene_intro->GOselected);

			if (ImGui::IsWindowHovered()) App->camera->isOnHierarchy = true;
			else App->camera->isOnHierarchy = false;

			if (openMenuHovering)
				DrawMenuHovering();
			else if (openMenuNotHovering)
				DrawMenuNotHovering();

			ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

			for (uint i = 0; i < App->scene_intro->gameobjectsList.size(); ++i)
			{

				if (ImGui::Selectable(App->scene_intro->gameobjectsList.at(i)->oData.GOname.data(), App->scene_intro->gameobjectsList.at(i), base_flags))
				{
					App->scene_intro->GOselected = App->scene_intro->gameobjectsList.at(i);

					switch (i) 
					{
						case 0:
							LOG_C("Selected GameObject i = %i", i);
							break;
						case 1:
							LOG_C("Selected GameObject i = %i", i);
							break;
					}
				}
				
				// Select active GO (Left Click)
				if (ImGui::IsItemClicked(0))
				{
					clickedGO = i;
					App->scene_intro->GOselected = App->scene_intro->gameobjectsList[i];
				}

				// Create Menus (Right Click)
				if (!ImGui::IsItemFocused() && ImGui::IsMouseClicked(1) && ImGui::IsWindowHovered())
				{
					openMenuNotHovering = true;
				}
				if (ImGui::IsItemClicked(1) && ImGui::IsWindowHovered())
				{
					openMenuHovering = true;
					clickedGO = i;
					App->scene_intro->GOselected = App->scene_intro->gameobjectsList[i];
				}

			}
			
		}

		ImGui::End();

	}

	return true;
}

void PanelHierarchy::DrawMenuNotHovering()
{
	if (ImGui::IsMouseReleased(0) || ImGui::IsMouseReleased(2))
		openMenuNotHovering = false;
	else if (ImGui::IsMouseClicked(1))
		openMenuNotHovering = false;

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::IsWindowHovered()) App->camera->isOnHierarchy = true;
		else App->camera->isOnHierarchy = false;

		if (ImGui::MenuItem("Create GameObject"))
		{
			App->scene_intro->CreateGO("GameObject_");
			openMenuHovering = false;
		}
		
		if (ImGui::BeginMenu("Create Shape"))
		{
			if (ImGui::MenuItem("Cube"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::B_CUBE);
				openMenuHovering = false;
			}

			if (ImGui::MenuItem("Sphere"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::B_SPHERE);
				openMenuHovering = false;
			}

			if (ImGui::MenuItem("Cone"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::B_CONE);
				openMenuHovering = false;
			}

			if (ImGui::MenuItem("Cylinder"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::B_CYLINDER);
				openMenuHovering = false;
			}

			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}

void PanelHierarchy::DrawMenuHovering()
{
	if (ImGui::IsMouseReleased(0) || ImGui::IsMouseReleased(2))
		openMenuHovering = false;
	else if (ImGui::IsMouseClicked(1))
		openMenuHovering = false;

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::IsWindowHovered()) App->camera->isOnHierarchy = true;
		else App->camera->isOnHierarchy = false;

		if (ImGui::MenuItem("Remove GameObject"))
		{
			if (App->scene_intro->GOselected != nullptr)
				App->scene_intro->RemoveSelectedGO(App->scene_intro->GOselected);
			openMenuHovering = false;
		}

		ImGui::EndPopup();
	}
}
