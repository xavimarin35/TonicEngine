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
		DrawFaceNormals(App->scene_intro->GOselected);

	if (showVertexNormals)

	return true;
}

void ComponentMesh::Draw()
{
	
	

	ImGui::Spacing();

	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Spacing();

		ImGui::Checkbox("Show Face Normals", &showFaceNormals);

	}

}

void ComponentMesh::DrawFaceNormals(GameObject* m)
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 1);

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

	glColor3f(1, 1, 1);
	glEnd();
}

void ComponentMesh::DrawVertexNormals(GameObject* mesh)
{
}
