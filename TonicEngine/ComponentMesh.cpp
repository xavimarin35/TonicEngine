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

	}

}

void ComponentMesh::DrawFaceNormals(GameObject* comp)
{

}

void ComponentMesh::DrawVertexNormals(Component* comp)
{
	
}
