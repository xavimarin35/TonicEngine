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

void ComponentTransform::DrawInspector()
{
	GameObject* go = App->scene_intro->GOselected;

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentTransform() != nullptr)
	{
		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
			go->GetComponentTransform()->Reset();

		if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			new_default = true;

		ImGui::Spacing();

		if (App->gui->CheckParent(go->GOparent))
		{
			ImGui::TextColored(RED_COLOR, "ImGuizmo not functional in this object");

			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("ImGuizmo is not updating this transform,\nit has only a visual purpose, but you can\ntry with another object outside the Dummy001");
			}

			ImGui::Spacing();
		}

		if (go->GetComponentCamera() == nullptr)
		{
			if (ImGui::Button(" Reset Transform "))
				Reset();

			if (ImGui::IsItemHovered())
			{
				char posX = ("%.2f", default_position.x); char posY = ("%.2f", default_position.y); char posZ = ("%.2f", default_position.z);
				char rotX = ("%.2f", default_rotation_e.x); char rotY = ("%.2f", default_rotation_e.y); char rotZ = ("%.2f", default_rotation_e.z);
				char scX = ("%.2f", default_scale.x); char scY = ("%.2f", default_scale.y); char scZ = ("%.2f", default_scale.z);

				std::string position, rotation, scale;

				position = ("( " + std::to_string(posX) + ", " + std::to_string(posY) + ", " + std::to_string(posZ) + (" )"));
				rotation = ("( " + std::to_string(rotX) + ", " + std::to_string(rotY) + ", " + std::to_string(rotZ) + (" )"));
				scale = ("( " + std::to_string(scX) + ", " + std::to_string(scY) + ", " + std::to_string(scZ) + (" )"));

				std::string toolTip = position + "\n" + rotation + "\n" + scale;

				ImGui::SetTooltip(toolTip.c_str());
			}

			ImGui::SameLine();

			if (ImGui::Button(" Set New Default "))
				new_default = true;

			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Save the actual transform to be the new default");
			}

			ImGui::SameLine();
			App->gui->HelpMarker("You can double-click in any box to write a value");

			ImGui::Spacing();
		}

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
		ImGui::PushItemWidth(65); ImGui::PushID("scaleX"); ImGui::DragFloat("X", &sc.x, 0.1F, 0.2F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("scaleY"); ImGui::DragFloat("Y", &sc.y, 0.1F, 0.2F); ImGui::PopID(); ImGui::SameLine();
		ImGui::PushItemWidth(65); ImGui::PushID("scaleZ"); ImGui::DragFloat("Z", &sc.z, 0.1F, 0.2F); ImGui::PopID();

		if (!GetScale().Equals(sc)) SetScale(sc);

		if (new_default)
		{
			SetNewDefault(pos, rot, sc);
			new_default = false;
		}
	}
}

void ComponentTransform::IsTransformComponentActive(GameObject* go)
{
	go = App->scene_intro->GOselected;

	if (go->GetComponentTransform()->active)
	{
		LOG_C("Transform Component is active");
	}
	else
	{
		LOG_C("ERROR: Transform Component is NOT active");
	}
}

void ComponentTransform::Save(uint GO_id, nlohmann::json& scene_file)
{
	scene_file[object->data.name]["Components"]["Transform"]["UUID"] = UUID;
	scene_file[object->data.name]["Components"]["Transform"]["PositionX"] = position.x;
	scene_file[object->data.name]["Components"]["Transform"]["PositionY"] = position.y;
	scene_file[object->data.name]["Components"]["Transform"]["PositionZ"] = position.z;
	scene_file[object->data.name]["Components"]["Transform"]["RotationX"] = rotation_euler.x;
	scene_file[object->data.name]["Components"]["Transform"]["RotationY"] = rotation_euler.y;
	scene_file[object->data.name]["Components"]["Transform"]["RotationZ"] = rotation_euler.z;
	scene_file[object->data.name]["Components"]["Transform"]["ScaleX"] = scale.x;
	scene_file[object->data.name]["Components"]["Transform"]["ScaleY"] = scale.y;
	scene_file[object->data.name]["Components"]["Transform"]["ScaleZ"] = scale.z;
}

void ComponentTransform::Reset(bool new_default)
{
	// Just Reset position to initial position
	if (!new_default)
	{
		this->position = default_position;
		this->scale = default_scale;
		this->rotation_quaternion = default_rotation_q;
		this->rotation_euler = default_rotation_e;

		ResetTransform();
	}
}

void ComponentTransform::ResetTransform()
{
	localMatrix = math::float4x4::FromTRS(position, rotation_quaternion, scale);
	rotation_euler = rotation_quaternion.ToEulerXYZ() * RADTODEG;

	moved = true;
}

void ComponentTransform::SetNewDefault(float3 pos, float3 rot, float3 sc)
{
	default_position = pos;
	default_rotation_e = rot;
	default_scale = sc;

	Reset();
}

void ComponentTransform::UpdateGizmo(float4x4 newMatrix)
{
	newMatrix.Decompose(position, rotation_quaternion, scale);

	rotation_euler = rotation_quaternion.ToEulerXYZ() * RADTODEG;

	SetPosition(position);
	SetEulerRotation(rotation_euler);
	SetScale(scale);

	globalMatrix = newMatrix;
}