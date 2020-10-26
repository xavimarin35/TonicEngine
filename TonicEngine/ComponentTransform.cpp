#include "ComponentTransform.h"
#include "ModuleGUI.h"

ComponentTransform::ComponentTransform(GameObject* gameObject, bool active) : Component(COMPONENT_TYPE::TRANSFORM, gameObject)
{
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::Draw()
{
	ImGui::Text("Position:");
	ImGui::SameLine(); ImGui::PushItemWidth(60);  ImGui::PushID("pos");
	ImGui::DragFloat("X", &position.x, 0.005f);
	ImGui::PopID();

	ImGui::SameLine(); ImGui::PushItemWidth(60);
	ImGui::PushID("pos");
	ImGui::DragFloat("Y", &position.y, 0.005f); ImGui::PopID();

	ImGui::SameLine();
	ImGui::PushItemWidth(60);  ImGui::PushID("pos");
	ImGui::DragFloat("Z", &position.z, 0.005f);
	ImGui::PopID();

	//Rotation

	ImGui::Text("Rotation:");
	ImGui::SameLine();
	ImGui::PushItemWidth(60);
	ImGui::PushID("rot");
	ImGui::DragFloat("X", &rotation.x, 0.005f);
	ImGui::PopID();

	ImGui::SameLine();
	ImGui::PushItemWidth(60);
	ImGui::PushID("rot");
	ImGui::DragFloat("Y", &rotation.y, 0.005f);
	ImGui::PopID();

	ImGui::SameLine();
	ImGui::PushItemWidth(60);
	ImGui::PushID("rot");
	ImGui::DragFloat("Z", &rotation.z, 0.005f);
	ImGui::PopID();

	//Scale

	ImGui::Text("Scale:   ");
	ImGui::SameLine();
	ImGui::PushItemWidth(60);
	ImGui::PushID("scale");
	ImGui::DragFloat("X", &scale.x, 0.005f);
	ImGui::PopID();

	ImGui::SameLine();
	ImGui::PushItemWidth(60);
	ImGui::PushID("scale");
	ImGui::DragFloat("Y", &scale.y, 0.005f);
	ImGui::PopID();

	ImGui::SameLine();
	ImGui::PushItemWidth(60);
	ImGui::PushID("scale");
	ImGui::DragFloat("Z", &scale.z, 0.005f);
	ImGui::PopID();
}
