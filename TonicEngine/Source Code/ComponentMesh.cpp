#include "ComponentMesh.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"

#include "ModuleResources.h"
#include "Resource.h"
#include "ResourceMesh.h"

ComponentMesh::ComponentMesh(GameObject* gameObject) : Component(COMPONENT_TYPE::MESH, gameObject)
{
	type = COMPONENT_TYPE::MESH;
}

ComponentMesh::~ComponentMesh()
{
	App->renderer3D->DeleteBuffer(rMesh->data.id_index);
	App->renderer3D->DeleteBuffer(rMesh->data.id_vertex);
	App->renderer3D->DeleteBuffer(rMesh->data.id_tex_coords);

	RELEASE_ARRAY(rMesh->data.vertex);
	RELEASE_ARRAY(rMesh->data.index);
	RELEASE_ARRAY(rMesh->data.tex_coords);
	RELEASE_ARRAY(rMesh->data.face_normals);
}

bool ComponentMesh::Update()
{
	return true;
}

bool ComponentMesh::CleanUp()
{
	if (rMesh != nullptr)
	{
		rMesh->references -= 1;
		rMesh->loaded -= 1;

		if (rMesh->loaded == 0)
			rMesh->ReleaseMemory();
	}

	return true;
}

void ComponentMesh::Draw()
{
	App->scene_intro->DrawGameObjectNodes(object);
}

void ComponentMesh::DrawInspector()
{
	ImGui::Spacing();

	GameObject* go = App->scene_intro->GOselected;

	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentMesh() != nullptr)
	{
		ImGui::Spacing();

		if (rMesh != nullptr)
		{
			ImGui::Text("Number of polygons:");
			ImGui::SameLine();
			ImGui::TextColored(YELLOW_COLOR, "%d", rMesh->data.num_index / 3);

			ImGui::Text("Number of vertices:");
			ImGui::SameLine();
			ImGui::TextColored(YELLOW_COLOR, "%d", rMesh->data.num_vertex);

			ImGui::Text("Number of indices:");
			ImGui::SameLine();
			ImGui::TextColored(YELLOW_COLOR, "%d", rMesh->data.num_index);

			ImGui::Separator();

			ImGui::Text("File:"); ImGui::SameLine();
			ImGui::TextColored(YELLOW_COLOR, go->GetComponentMesh()->rMesh->exported_file.c_str());
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextColored(GREY_COLOR, "%s", go->GetComponentMesh()->rMesh->exported_file.c_str());
				ImGui::EndTooltip();
			}

			ImGui::Spacing();

			ImGui::Text("Source File:"); ImGui::SameLine();
			ImGui::TextColored(YELLOW_COLOR, go->GetComponentMesh()->rMesh->file.c_str());
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextColored(GREY_COLOR, "%s", go->GetComponentMesh()->rMesh->file.c_str());
				ImGui::EndTooltip();
			}
		}
	}
}

void ComponentMesh::IsMeshComponentActive(GameObject* go)
{
	go = App->scene_intro->GOselected;

	if (go->GetComponentMesh()->active)
	{
		LOG_C("Mesh Component is active");
	}
	else
	{
		LOG_C("ERROR: Mesh Component is NOT active");
	}		
}

void ComponentMesh::Save(uint GO_id, nlohmann::json& scene)
{
	scene[object->data.name]["Components"]["Mesh"]["UUID"] = UUID;
	if (rMesh != nullptr)
		scene[object->data.name]["Components"]["Mesh"]["Name"] = App->GetPathName(rMesh->exported_file);
}

const AABB& ComponentMesh::BoundingBox() 
{ 
	return aabb; 
}