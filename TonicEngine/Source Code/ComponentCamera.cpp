#include "ComponentCamera.h"
#include "ModuleInput.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"

#include "MathGeoLib/include/Math/MathFunc.h"

ComponentCamera::ComponentCamera(GameObject* GO) : Component(COMPONENT_TYPE::CAMERA, GO)
{
	type = COMPONENT_TYPE::CAMERA;

	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 200.0f;
	frustum.verticalFov = DegToRad(60.0f);
	
	AspectRatio(1.3f);
}

ComponentCamera::~ComponentCamera()
{
}

bool ComponentCamera::Start()
{
	return true;
}

bool ComponentCamera::Update()
{
	ComponentTransform* transf = object->GetComponentTransform();

	frustum.pos = transf->GetGlobalTransform().TranslatePart();
	frustum.front = transf->GetGlobalTransform().WorldZ();
	frustum.up = transf->GetGlobalTransform().WorldY();

	if (seeFrustum)
		DrawFrustum();

	return true;
}

void ComponentCamera::DrawCamera()
{
	if (showFrustum || App->scene_intro->GOselected == object)
		DrawFrustum();
}

bool ComponentCamera::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

void ComponentCamera::DrawInspector()
{
	ImGui::Spacing();

	GameObject* go = App->scene_intro->GOselected;

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

	if (ImGui::CollapsingHeader("Camera"), flags && go->GetComponentCamera() != nullptr)
	{
		ImGui::Spacing();

		if (ImGui::Button("Set as Game Camera"))
		{
			App->camera->playCam = go;
		}

		ImGui::SameLine();

		App->gui->HelpMarker("Select this camera to be the active one when entering into Play Mode");

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Checkbox("Draw Frustum", &this->seeFrustum);

		ImGui::Spacing();

		if (ImGui::Checkbox("Camera Culling", &this->showFrustum))
		{
			if (this->showFrustum)
			{
				if (App->renderer3D->culling != nullptr)
					App->renderer3D->culling->showFrustum = false;

				App->renderer3D->culling = this;
			}
			else
				App->renderer3D->culling = nullptr;
		}

		ImGui::Spacing();
		ImGui::Separator();

		float nearPlane = GetNearPlane();
		float farPlane = GetFarPlane();
		float fov = GetFOV();
		float ratio = GetRatio();

		if (ImGui::TreeNodeEx("Planes", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Spacing();

			ImGui::PushItemWidth(180);
			ImGui::SliderFloat("Near Plane", &nearPlane, 0.1f, farPlane);

			ImGui::Spacing();

			ImGui::PushItemWidth(180);
			ImGui::SliderFloat("Far Plane", &farPlane, nearPlane, 400.f);
			
			ImGui::TreePop();
		}

		ImGui::Spacing();

		if (ImGui::TreeNodeEx("Properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::Spacing();

			ImGui::PushItemWidth(180);
			ImGui::SliderFloat("Field of View", &fov, 0.1f, 179.f);

			ImGui::Spacing();

			ImGui::PushItemWidth(180);
			ImGui::SliderFloat("Aspect Ratio", &ratio, 0.1f, 10.f);

			ImGui::TreePop();
		}

		if (nearPlane != GetNearPlane()) SetNearPlane(nearPlane);
		if (farPlane != GetFarPlane()) SetFarPlane(farPlane);
		if (fov != GetFOV()) SetFOV(fov);
		if (ratio != GetRatio()) SetRatio(ratio);
	}
}

void ComponentCamera::LookAt(const float3& position)
{
	float3 dir = position - frustum.pos;

	float3x3 m = float3x3::LookAt(frustum.front, dir.Normalized(), frustum.up, float3::unitY);

	frustum.front = m.MulDir(frustum.front).Normalized();
	frustum.up = m.MulDir(frustum.up).Normalized();
}

float ComponentCamera::GetFOV() const
{
	return  frustum.verticalFov * RADTODEG;
}

float ComponentCamera::GetNearPlane() const
{
	return frustum.nearPlaneDistance;
}

float ComponentCamera::GetFarPlane() const
{
	return frustum.farPlaneDistance;
}

float ComponentCamera::GetRatio() const
{
	return frustum.AspectRatio();
}

void ComponentCamera::SetNearPlane(float dist)
{
	if (dist > 0.0f && dist < frustum.farPlaneDistance)
	{
		frustum.nearPlaneDistance = dist;
		update_frustum = true;
	}
}

void ComponentCamera::SetFarPlane(float dist)
{
	if (dist > 0.0f && dist > frustum.nearPlaneDistance)
	{
		frustum.farPlaneDistance = dist;
		update_frustum = true;
	}
}

void ComponentCamera::SetFOV(float fov)
{
	float aspect_ratio = frustum.AspectRatio();

	frustum.verticalFov = DegToRad(fov);
	SetRatio(aspect_ratio);

	update_frustum = true;
}

void ComponentCamera::SetRatio(float aspect_ratio)
{
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspect_ratio);
	update_frustum = true;
}

void ComponentCamera::DrawFrustum()
{
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	
	float3 corners[8];
	frustum.GetCornerPoints(corners);

	glColor3f(App->gui->frustum_color.r, App->gui->frustum_color.g, App->gui->frustum_color.b);

	// Left Face
	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[1].x, corners[1].y, corners[1].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[3].x, corners[3].y, corners[3].z);

	// Right Face
	glVertex3f(corners[4].x, corners[4].y, corners[4].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[6].x, corners[6].y, corners[6].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	// Near-Far
	glColor3f(App->gui->plane_color.r, App->gui->plane_color.g, App->gui->plane_color.b);

	// Near Plane
	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[4].x, corners[4].y, corners[4].z);

	glVertex3f(corners[2].x, corners[2].y, corners[2].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	glVertex3f(corners[0].x, corners[0].y, corners[0].z);
	glVertex3f(corners[2].x, corners[2].y, corners[2].z);

	glVertex3f(corners[4].x, corners[4].y, corners[4].z);
	glVertex3f(corners[6].x, corners[6].y, corners[6].z);

	// Far Plane
	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[5].x, corners[5].y, corners[5].z);

	glVertex3f(corners[3].x, corners[3].y, corners[3].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glVertex3f(corners[1].x, corners[1].y, corners[1].z);
	glVertex3f(corners[3].x, corners[3].y, corners[3].z);

	glVertex3f(corners[5].x, corners[5].y, corners[5].z);
	glVertex3f(corners[7].x, corners[7].y, corners[7].z);

	glColor3f(App->gui->frustum_color.r, App->gui->frustum_color.g, App->gui->frustum_color.b);
	glEnd();

}

void ComponentCamera::AspectRatio(float ratio)
{
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) * ratio);

	update_frustum = true;
}

float4x4 ComponentCamera::GetViewMatrix() const
{
	return frustum.ViewMatrix();
}

float4x4 ComponentCamera::GetView() const
{
	return float4x4(frustum.ViewMatrix()).Transposed();
}

float4x4 ComponentCamera::GetProjectionMatrix() const
{
	return float4x4::D3DPerspProjRH(frustum.nearPlaneDistance, frustum.farPlaneDistance, frustum.NearPlaneWidth(), frustum.NearPlaneHeight());
}

float4x4 ComponentCamera::GetProjection() const
{
	return frustum.ProjectionMatrix().Transposed();
}

Ray ComponentCamera::EyeRay(float x, float y) const
{
	return frustum.UnProject(x, y);
}

Ray ComponentCamera::NearRay(float x, float y) const
{
	return frustum.UnProjectFromNearPlane(x, y);
}

LineSegment ComponentCamera::NearSegment(float x, float y) const
{
	return frustum.UnProjectLineSegment(x, y);
}

bool ComponentCamera::Intersect(const AABB& box) const
{
	return Intersect(frustum, box);
}

bool ComponentCamera::Intersect(const Frustum& frustum_, const AABB& box)
{
	float3 corners[8];
	box.GetCornerPoints(corners);

	math::Plane p[6];
	frustum_.GetPlanes(p);

	uint inside = 0;

	for (int i = 0; i < 6; ++i)
	{
		int count = 8;

		for (int j = 0; j < 8; ++j)
		{
			if (p[i].IsOnPositiveSide(corners[j])) --count;
		}

		if (count == 0) return false;
		else inside += 1;
	}

	return true;
}

void ComponentCamera::Save(uint GO_id, nlohmann::json& scene_file)
{
	scene_file[object->data.name]["Components"]["Camera"]["ShowFrustum"] = seeFrustum;
	scene_file[object->data.name]["Components"]["Camera"]["DoCulling"] = showFrustum;
	scene_file[object->data.name]["Components"]["Camera"]["FrustumFarPlane"] = frustum.farPlaneDistance;
	scene_file[object->data.name]["Components"]["Camera"]["FrustumNearPlane"] = frustum.nearPlaneDistance;
}
