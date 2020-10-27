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

void ComponentMesh::Draw()
{
	ImGui::Spacing();


	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Spacing();

		ImGui::Checkbox("Show Face Normals", &App->scene_intro->GOselected->GetComponentMesh()->showFaceNormals);

	}

}

void ComponentMesh::DrawFaceNormals(Component* mesh)
{
	//glBegin(GL_LINES);
	//glColor3f(1, 0, 1);

	//float3* normals_faces = new float3[mData.num_index];
	//float3* normals_faces_vector = new float3[mData.num_index];
	//for (int j = 0; j < mData.num_index; j += 3)
	//{
	//	// Declaring each vertex of the triangle
	//	float3 vert1 = mData.vertex[mData.index[j]];
	//	float3 vert2 = mData.vertex[mData.index[j + 1]];
	//	float3 vert3 = mData.vertex[mData.index[j + 2]];

	//	normals_faces[j] = (vert1 + vert2 + vert3) / 3;

	//	// Get normal vector with cross product
	//	float3 edge_a = vert2 - vert1;
	//	float3 edge_b = vert3 - vert1;

	//	float3 normal;
	//	normal = Cross(edge_a, edge_b);
	//	normal.Normalize();

	//	normals_faces_vector[j] = normal;
	//}

	//for (int i = 0; i < mesh->mData.num_index; ++i)
	//{
	//	glVertex3f(normals_faces[i].x, normals_faces[i].y, normals_faces[i].z);
	//	glVertex3f(normals_faces[i].x + normals_faces_vector[i].x,
	//		normals_faces[i].y + normals_faces_vector[i].y,
	//		normals_faces[i].z + normals_faces_vector[i].z);
	//}
	//glColor3f(1, 1, 1);
	//glEnd();
}

void ComponentMesh::DrawVertexNormals(Component* mesh)
{
	/*glBegin(GL_LINES);
	glColor3f(0, 1, 0);

	for (int i = 0; i < mesh->mData.num_vertex; ++i)
	{
		glVertex3f(mesh->mData.vertex[i].x, mesh->mData.vertex[i].y, mesh->mData.vertex[i].z);
		glVertex3f(mesh->mData.vertex[i].x + mesh->mData.normals_vector[i].x,
			mesh->mData.vertex[i].y + mesh->mData.normals_vector[i].y,
			mesh->mData.vertex[i].z + mesh->mData.normals_vector[i].z);
	}
	glColor3f(1, 1, 1);
	glEnd();
	}*/
}
