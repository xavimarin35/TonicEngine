#include "ComponentCamera.h"
#include "ModuleInput.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"

ComponentCamera::ComponentCamera(GameObject* GO) : Component(COMPONENT_TYPE::CAMERA, GO)
{
	type = COMPONENT_TYPE::CAMERA;

	X = vec3(1.0f, 0.0f, 0.0f);
	Y = vec3(0.0f, 1.0f, 0.0f);
	Z = vec3(0.0f, 0.0f, 1.0f);

	Position = vec3(0.0f, 0.0f, 5.0f);
	Reference = vec3(0.0f, 0.0f, 0.0f);
}

ComponentCamera::~ComponentCamera()
{}

bool ComponentCamera::Start()
{
	return true;
}

bool ComponentCamera::Update()
{
	return true;
}

bool ComponentCamera::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

void ComponentCamera::Draw()
{
	ImGui::Spacing();

	GameObject* go = App->scene_intro->GOselected;

	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen) && go->GetComponentCamera() != nullptr)
	{
		
	}
}

void ComponentCamera::LookAt(const float3& position)
{

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

void ComponentCamera::DrawFrustum()
{
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glColor4f(Red.r, Red.g, Red.b, Red.a);

	for (uint i = 0; i < frustum.NumEdges(); i++)
	{
		glVertex3f(frustum.Edge(i).a.x, frustum.Edge(i).a.y, frustum.Edge(i).a.z);
		glVertex3f(frustum.Edge(i).b.x, frustum.Edge(i).b.y, frustum.Edge(i).b.z);
	}

	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

