#include "ComponentMesh.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"

ComponentMesh::ComponentMesh(GameObject* gameObject, bool active) : Component(COMPONENT_TYPE::MESH, gameObject)
{
	type = COMPONENT_TYPE::MESH;
}

ComponentMesh::~ComponentMesh()
{
}

bool ComponentMesh::Update()
{
	
	if (showFaceNormals)
	{
		DrawFaceNormals(App->scene_intro->GOselected, true);
	}
	else
		DrawFaceNormals(App->scene_intro->GOselected, false);
	

	if (showVertexNormals)

	return true;
}

void ComponentMesh::Draw()
{
	
	ImGui::Spacing();

	GameObject* go = App->scene_intro->GOselected;

	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Spacing();

		ImGui::Text("Number of polygons:");
		ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, "%d", mData.num_index / 3);

		ImGui::Text("Number of vertices:");
		ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, "%d", mData.num_vertex);

		ImGui::Text("Number of indices:");
		ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, "%d", mData.num_index);

		ImGui::Separator();

		ImGui::Text("File:"); ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, go->GetComponentMesh()->mData.path.c_str());

		ImGui::Separator();

		if (ImGui::TreeNode("Face Normals:")) {
			ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueBar;
			ImGui::Text("Draw:  "); ImGui::SameLine(); ImGui::PushItemWidth(110); ImGui::PushID("drawF"); ImGui::Checkbox(" ", &showFaceNormals); ImGui::PopID();
			ImGui::Text("Length:");	ImGui::SameLine(); ImGui::PushItemWidth(130); ImGui::PushID("lenghtF"); ImGui::InputFloat(" ", &go->GetComponentMesh()->faceLenght, 0.1f, 4.0f); ImGui::PopID(); 
			ImGui::Text("Color: "); ImGui::SameLine(); ImGui::PushItemWidth(150); ImGui::ColorEdit3(" ", (float*)&go->GetComponentMesh()->faceColor, flags);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Vertex Normals:")) {
			ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueBar;
			ImGui::Text("Draw:  "); ImGui::SameLine(); ImGui::PushItemWidth(110); ImGui::PushID("drawV"); ImGui::Checkbox(" ", &showVertexNormals); ImGui::PopID();
			ImGui::Text("Length:");	ImGui::SameLine(); ImGui::PushItemWidth(130); ImGui::PushID("lenghtV"); ImGui::InputFloat(" ", &go->GetComponentMesh()->vertexLenght, 0.1f, 4.0f); ImGui::PopID();
			ImGui::Text("Color: "); ImGui::SameLine(); ImGui::PushItemWidth(150); ImGui::ColorEdit3(" ", (float*)&go->GetComponentMesh()->vertexColor, flags);
			ImGui::TreePop();
		}

	}

}

bool ComponentMesh::DrawFaceNormals(GameObject* m, bool active)
{
	if (active)
	{

		float3 mid;
		float3 normal;

		for (int j = 0; j < m->GetComponentMesh()->mData.num_index; j += 3)
		{
			// Declaring each vertex of the triangle
			float3 vert1 = m->GetComponentMesh()->mData.vertex[m->GetComponentMesh()->mData.index[j]];
			float3 vert2 = m->GetComponentMesh()->mData.vertex[m->GetComponentMesh()->mData.index[j + 1]];
			float3 vert3 = m->GetComponentMesh()->mData.vertex[m->GetComponentMesh()->mData.index[j + 2]];

			mid = (vert1 + vert2 + vert3) / 3;

			// Get normal vector with cross product
			float3 edge_a = vert2 - vert1;
			float3 edge_b = vert3 - vert1;

			normal = Cross(edge_a, edge_b);
			normal.Normalize();

			glBegin(GL_LINES);
			glColor3f(m->GetComponentMesh()->faceColor.r, m->GetComponentMesh()->faceColor.g, m->GetComponentMesh()->faceColor.b);

			glVertex3f(mid.x, mid.y, mid.z);
			glVertex3f(mid.x + normal.x * m->GetComponentMesh()->faceLenght, mid.y + normal.y * m->GetComponentMesh()->faceLenght, mid.z + normal.z * m->GetComponentMesh()->faceLenght);

		}

		glEnd();
	}
	else 
	{
		return false;
	}
	
}

bool ComponentMesh::DrawVertexNormals(GameObject* mesh, bool active)
{
	if (active)
	{

	}
	else
	{
		return false;
	}
	
}
