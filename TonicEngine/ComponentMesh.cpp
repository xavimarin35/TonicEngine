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

		ImGui::Checkbox("Face Normals", &showFaceNormals); ImGui::SameLine();
		ImGui::Checkbox("Vertex Normals", &showVertexNormals);

		ImGui::Separator();

		ImGui::Text("File:"); ImGui::SameLine();
		ImGui::TextColored(YELLOW_COLOR, go->GetComponentMesh()->mData.path.c_str());

	}

}

bool ComponentMesh::DrawFaceNormals(GameObject* m, bool active)
{
	if (active)
	{
		glBegin(GL_LINES);
		glColor3f(0, 0, 1);

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

			glVertex3f(mid.x, mid.y, mid.z);
			glVertex3f(mid.x + normal.x, mid.y + normal.y, mid.z + normal.z);
		}

		glColor3f(0, 1, 1);
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
