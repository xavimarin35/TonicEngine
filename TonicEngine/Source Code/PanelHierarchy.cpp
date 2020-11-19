#include "PanelHierarchy.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "MeshImporter.h"
#include "ModuleCamera3D.h"

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
			if (ImGui::IsWindowHovered()) App->camera->isOnHierarchy = true;
			else App->camera->isOnHierarchy = false;

			if (openMenuHovering)
				DrawMenuHovering();
			else if (openMenuNotHovering)
				DrawMenuNotHovering();

			ManageNodesOnHierarchy(App->scene_intro->GOroot);
		}

		ImGui::End();
	}

	return true;
}

void PanelHierarchy::ManageNodesOnHierarchy(GameObject* GO)
{
	ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
	ImGuiTreeNodeFlags node_flag = flag;

	ImVec4 c = { 1.0f, 1.0f, 1.0f, 1.0f };

	if (GO == App->scene_intro->GOselected)
		node_flag |= ImGuiTreeNodeFlags_Selected;

	// if GOs are not active, print them grey
	if (!GO->data.active)
		c = { 0.5f, 0.5f, 0.5f, 1.0f };

	ImGui::PushStyleColor(ImGuiCol_Text, c);

	bool node_open = false;

	if (GO->data.active == true)
		node_open = ImGui::TreeNodeEx((void*)(intptr_t)GO->data.id, node_flag, GO->data.name.c_str());
	else 
		node_open = ImGui::TreeNodeEx((void*)(intptr_t)GO->data.id, node_flag |= ImGuiTreeNodeFlags_Leaf, GO->data.name.c_str());

	// when node is clicked
	if (ImGui::IsItemClicked(0))
		App->scene_intro->GOselected = GO;

	// Deselect GO when right-clicking in the hierarchy window 
	if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
		App->scene_intro->GOselected = nullptr;

	// Delete with SUPR
	if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
		App->scene_intro->RemoveSelectedGO(App->scene_intro->GOselected);

	// Create menu when item is selected
	if (ImGui::IsItemClicked(1) && ImGui::IsWindowHovered())
	{
		openMenuHovering = true;
		App->scene_intro->GOselected = GO;
	}

	// Create menu when item is not selected (Right Click)
	if (ImGui::IsMouseClicked(1) && ImGui::IsWindowHovered())
		openMenuNotHovering = true;

	// not working payload yet
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("DRAG GO", GO, sizeof(GameObject));
		ImGui::TextColored(YELLOW_COLOR, "Drag %s", GO->data.name.c_str());
		draggedGO = GO;

		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Node Dragged"))
		{
			GO->AddChild(draggedGO); 
			draggedGO = nullptr;
		}

		ImGui::EndDragDropTarget();
	}

	// If node is opened
	if (node_open)
	{
		// If list has childs
		if (!GO->childrenList.empty())
		{
			// Draw childs
			for (std::vector<GameObject*>::iterator iterator = GO->childrenList.begin(); iterator != GO->childrenList.end(); iterator++)
			{
				ManageNodesOnHierarchy(*iterator);
			}
		}

		ImGui::TreePop();
	}

	ImGui::PopStyleColor();
}


void PanelHierarchy::DrawMenuNotHovering()
{
	if (ImGui::IsMouseClicked(1))
		openMenuNotHovering = false;

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::IsWindowHovered()) App->camera->isOnHierarchy = true;
		else App->camera->isOnHierarchy = false;

		if (ImGui::MenuItem("Create Empty GameObject"))
		{
			GameObject* go = App->scene_intro->CreateGO("Empty");
			App->scene_intro->GOroot->AddChild(go);

			openMenuHovering = false;
		}

		ImGui::Separator();
		
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

			ImGui::Separator();

			if (ImGui::MenuItem("Baker House"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::BAKER_HOUSE);
				openMenuHovering = false;
			}

			if (ImGui::MenuItem("Street"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::STREET);
				openMenuHovering = false;
			}

			ImGui::EndMenu();
		}

		App->gui->HelpMarker("Game assets from The Witcher: Ties of Destiny");
		ImGui::SameLine();

		if (ImGui::BeginMenu("Create Other"))
		{
			if (ImGui::MenuItem("Geralt of Rivia"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::GERALT);
				LOG_C("WARNING: This 3D model has so many polys. The performance of the engine could be affected");
				openMenuHovering = false;
			}

			if (ImGui::MenuItem("Light Post"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::LIGHTPOST);
				openMenuHovering = false;
			}

			if (ImGui::MenuItem("Carriage"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::CARRIAGE);
				openMenuHovering = false;
			}

			if (ImGui::MenuItem("Rock"))
			{
				App->scene_intro->Create3DObject(OBJECTS3D::ROCK);
				openMenuHovering = false;
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Visit Ties of Destiny!"))
			{
				App->RequestBrowser("https://tiesofdestiny.com/index.html");
				openMenuHovering = false;
			}

			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}

void PanelHierarchy::DrawMenuHovering()
{
	if (ImGui::IsMouseClicked(1))
		openMenuHovering = false;

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::IsWindowHovered()) App->camera->isOnHierarchy = true;
		else App->camera->isOnHierarchy = false;

		if (ImGui::MenuItem("Create Empty Child"))
		{
			App->scene_intro->CreateGO("Empty Child", App->scene_intro->GOselected);
		}

		if (ImGui::MenuItem("Remove GameObject"))
		{
			if (App->scene_intro->GOselected != nullptr)
				App->scene_intro->RemoveSelectedGO(App->scene_intro->GOselected);
			openMenuHovering = false;
		}

		ImGui::EndPopup();
	}
}