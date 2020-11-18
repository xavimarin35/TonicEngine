#include "ComponentTransform.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"

ComponentTransform::ComponentTransform(GameObject* gameObject) : Component(COMPONENT_TYPE::TRANSFORM, gameObject)
{
	type = COMPONENT_TYPE::TRANSFORM;
}

ComponentTransform::~ComponentTransform()
{
}

float4x4 ComponentTransform::GetTransform() const { return localMatrix; }

float3 ComponentTransform::GetPosition() const { return position; }

Quat ComponentTransform::GetQuatRotation() const { return rotation_quaternion; }

float3 ComponentTransform::GetEulerRotation() const { return rotation_euler; }

float3 ComponentTransform::GetScale() const { return scale; }

float4x4 ComponentTransform::GetGlobalTransform() const { return globalMatrix; }

void ComponentTransform::SetPosition(float3& position)
{
	this->position = position;

	UpdateLocalTransform();
}

void ComponentTransform::SetEulerRotation(float3 rotation)
{
	float3 rot = (rotation - rotation_euler) * DEGTORAD;

	Quat quaternion_rot = Quat::FromEulerXYZ(rot.x, rot.y, rot.z);

	rotation_quaternion = rotation_quaternion * quaternion_rot;
	rotation_euler = rotation;

	UpdateLocalTransform();
}

void ComponentTransform::SetScale(float3& scale)
{
	if (scale.x > 0.0f && scale.y > 0.0f && scale.z > 0.0f) this->scale = scale;

	UpdateLocalTransform();
}

void ComponentTransform::SetGlobalTransform(float4x4 transform)
{
	localMatrix = transform.Inverted() * globalMatrix;
	globalMatrix = transform;

	TransformGlobalMat(globalMatrix);
}

void ComponentTransform::TransformGlobalMat(const float4x4& global)
{
	globalMatrix = global * localMatrix;

	UpdateTransform();

	moved = false;
}

void ComponentTransform::UpdateLocalTransform()
{
	localMatrix = math::float4x4::FromTRS(position, rotation_quaternion, scale);

	moved = true;
}

void ComponentTransform::UpdateTransform()
{
	localMatrix.Decompose(position, rotation_quaternion, scale);

	rotation_euler = rotation_quaternion.ToEulerXYZ() * RADTODEG;
}

void ComponentTransform::Draw()
{
	GameObject* go = App->scene_intro->GOselected;

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentTransform() != nullptr)
	{
		ImGui::Spacing();

		if (ImGui::Button(" Reset Transform ")) 
			Reset();
		
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(" Position: (0, 0, 0) \n Rotation: (0, 0, 0) \n Scale:    (1, 1, 1)");

		ImGui::SameLine();
		App->gui->HelpMarker("You can double-click in any box to write a value");

		ImGui::Spacing();

		float3 pos = GetPosition();
		ImGui::Text("Position"); ImGui::SameLine(); 
		
		ImGui::PushItemWidth(65); ImGui::PushID("posX"); ImGui::DragFloat("X", &pos.x, 0.5F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("posY"); ImGui::DragFloat("Y", &pos.y, 0.5F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("posZ"); ImGui::DragFloat("Z", &pos.z, 0.5F);ImGui::PopID();

		if (!GetPosition().Equals(pos)) SetPosition(pos);

		ImGui::Spacing();

		float3 rot = GetEulerRotation();
		ImGui::Text("Rotation"); ImGui::SameLine();

		ImGui::PushItemWidth(65); ImGui::PushID("rotX"); ImGui::DragFloat("X", &rot.x, 0.1F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("rotY"); ImGui::DragFloat("Y", &rot.y, 0.1F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("rotZ"); ImGui::DragFloat("Z", &rot.z, 0.1F); ImGui::PopID();

		if (!GetEulerRotation().Equals(rot)) SetEulerRotation(rot);

		ImGui::Spacing();

		float3 sc = GetScale();
		ImGui::Text("Scale   "); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("scaleX"); ImGui::DragFloat("X", &sc.x, 0.5F, 0.2F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("scaleY"); ImGui::DragFloat("Y", &sc.y, 0.5F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("scaleZ"); ImGui::DragFloat("Z", &sc.z, 0.5F); ImGui::PopID();

		if (!GetScale().Equals(sc)) SetScale(sc);
	}
}

void ComponentTransform::IsTransformComponentActive(GameObject* go)
{
	go = App->scene_intro->GOselected;

	if (go->GetComponentMesh()->active)
	{
		LOG_C("Transform Component is active");
	}
	else
	{
		LOG_C("ERROR: Transform Component is NOT active");
	}
}

void ComponentTransform::Reset(bool new_default)
{
	// Just Reset position to initial position
	if (!new_default)
	{
		this->position = float3::zero;
		this->scale = float3::one;
		this->rotation_quaternion = Quat::identity;

		ResetTransform();
	}
}

void ComponentTransform::ResetTransform()
{
	localMatrix = math::float4x4::FromTRS(position, rotation_quaternion, scale);
	rotation_euler = rotation_quaternion.ToEulerXYZ() * RADTODEG;

	moved = true;
}