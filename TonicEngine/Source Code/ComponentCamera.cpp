#include "ComponentCamera.h"
#include "ModuleInput.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"

#include "MathGeoLib/include/Math/MathFunc.h"

ComponentCamera::ComponentCamera(GameObject* GO) : Component(COMPONENT_TYPE::CAMERA, GO)
{
	type = COMPONENT_TYPE::CAMERA;

	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 1000.0f;
	frustum.verticalFov = DegToRad(60.0f);
	
	AspectRatio(1.3f);
}

ComponentCamera::~ComponentCamera()
{}

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

	return true;
}

void ComponentCamera::Draw2()
{
	if (showFrustrum || App->scene_intro->GOselected == object)
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

		if (ImGui::Checkbox("Culling", &this->showFrustrum))
		{
			if (this->showFrustrum)
			{
				if (App->renderer3D->culling != nullptr)
					App->renderer3D->culling->showFrustrum = false;

				App->renderer3D->culling = this;
			}
			else
				App->renderer3D->culling = nullptr;
		}

		ImGui::Separator();

		float nearPlane = GetNearPlane();
		float farPlane = GetFarPlane();
		float fov = GetFOV();
		float ratio = GetRatio();

		ImGui::Text("Near Plane"); ImGui::SameLine(130.f); ImGui::DragFloat("##NearPlane", &nearPlane, 0.05f, 0.1f, farPlane);
		ImGui::Text("Far Plane"); ImGui::SameLine(130.f); ImGui::DragFloat("##FarPlane", &farPlane, 0.05f, nearPlane, 5000.f);
		ImGui::Text("FOV"); ImGui::SameLine(130.f); ImGui::DragFloat("##FOV", &fov, 0.05f, 1.f, 179.f);
		ImGui::Text("Aspect Ratio"); ImGui::SameLine(130.f); ImGui::DragFloat("##AspectRatio", &ratio, 0.05f, 0.1f, 10.f);

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

	glColor3f(1.f, 1.f, 1.f);

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
	glColor3f(1.f, 0.f, 0.f);

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

	glColor3f(1, 1, 1);
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