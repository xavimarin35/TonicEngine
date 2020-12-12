#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "imgui-1.78/ImGuizmo.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	mainCam = new ComponentCamera();
	activeCam = new ComponentCamera();
	mainCam = activeCam;
}

ModuleCamera3D::~ModuleCamera3D()
{
	delete mainCam;
}

bool ModuleCamera3D::Start()
{
	mainCam->frustum.farPlaneDistance = 300;

	mainCam->frustum.pos = float3(26.f, 86.f, -90.f);

	cameraGO = App->scene_intro->CreateGO("Main_Camera", App->scene_intro->GOroot);
	cameraGO->CreateComponent(COMPONENT_TYPE::CAMERA);

	// default in Play Mode
	playCam = cameraGO;

	return true;
}

bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");
	RELEASE(mainCam);

	return true;
}

update_status ModuleCamera3D::Update(float dt)
{
	if (ImGuizmo::IsUsing() == true)
		return UPDATE_CONTINUE;

	if (CheckMousePosition())
	{
		mouse_picking = false;

		// Trying to focus while hovering a menu
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && !focusError)
		{
			LOG_C("WARNING: You have to be inside the scene to focus the camera to the selected GameObject");
			focusError = true;
		}

		return UPDATE_CONTINUE;
	}

	mouse_picking = true;
	focusError = false;

	float3 speed = 
	{ 
		(float)-App->input->GetMouseXMotion() * dt,
		(float)-App->input->GetMouseYMotion() * dt,
		(float)App->input->GetMouseZ() * dt
	};

	if (App->input->GetMouseZ() != 0)
		Zoom(speed.z * slow * mouseWheelS);

	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		mouse_picking = false;

		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT)
			Orbit(speed.x / slow, speed.y / slow);

		else if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
			Zoom(-speed.y * slow);
	}

	else if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		Rotate(speed.x / slow, speed.y / slow);
		
		float moveSpeed = currentSpeed * dt;

		MoveCamera(moveSpeed);
	}

	else if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
	{
		DragCamera(speed.x / (slow * 5.f), speed.y / (slow * 5.f));
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		if (App->scene_intro->GOselected != nullptr)
		{
			Focus(App->scene_intro->GOselected);
		}
	}

	DrawRay();

	return UPDATE_CONTINUE;	
}

void ModuleCamera3D::LookAt(const float3& Spot, float distance)
{
	looking_at = Spot;

	activeCam->LookAt(looking_at);

	if (distance > 0.f)
	{
		activeCam->frustum.pos = looking_at - activeCam->frustum.front * distance;
	}
}

void ModuleCamera3D::Move(const float3 &Movement)
{
	activeCam->frustum.pos += Movement;
	looking_at += Movement;
}

void ModuleCamera3D::Focus(GameObject* go)
{
	if (go != nullptr)
	{
		float dist = Length({ distanceFocus, distanceFocus, distanceFocus });
		float3 pos;

		ComponentTransform* transf = (ComponentTransform*)go->GetComponent(COMPONENT_TYPE::TRANSFORM);
		ComponentMesh* mesh = (ComponentMesh*)go->GetComponent(COMPONENT_TYPE::MESH);

		if (mesh != nullptr)
		{
			pos = go->aabb.CenterPoint();
		}
		else
		{
			pos = transf->position;
		}

		LookAt(pos, dist);
	}
}

void ModuleCamera3D::MoveCamera(float& speed)
{
	float3 mov(float3::zero);

	float3 right(activeCam->frustum.WorldRight());
	float3 front(activeCam->frustum.front);

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT) speed *= 5.0f;

	// Forward/Backwards
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) mov += front;
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) mov -= front;

	// Left/Right
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) mov -= right;
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) mov += right;

	// Down/Up
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) mov -= float3::unitY;
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) mov += float3::unitY;

	if (!mov.Equals(float3::zero))
		activeCam->frustum.Translate(mov * speed);
}

void ModuleCamera3D::DragCamera(float delta_x, float delta_y)
{
	ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);

	float3 mov(float3::zero);

	mov += activeCam->frustum.WorldRight() * delta_x;
	mov -= activeCam->frustum.up * delta_y;

	activeCam->frustum.Translate(mov * 100.f);
	looking_at += mov * 100.f;
}

void ModuleCamera3D::Zoom(float delta_z)
{
	activeCam->frustum.pos += activeCam->frustum.front * delta_z;
}

void ModuleCamera3D::Orbit(float motion_x, float motion_y)
{
	float3 focus = activeCam->frustum.pos - looking_at;

	Quat qy(activeCam->frustum.up, motion_x);
	Quat qx(activeCam->frustum.WorldRight(), motion_y);

	focus = qx.Transform(focus);
	focus = qy.Transform(focus);

	activeCam->frustum.pos = focus + looking_at;

	LookAt(looking_at);
}

void ModuleCamera3D::Rotate(float motion_x, float motion_y)
{
	if (motion_x != 0.f)
	{
		Quat q = Quat::RotateY(motion_x);
		activeCam->frustum.front = q.Mul(activeCam->frustum.front).Normalized();
		activeCam->frustum.up = q.Mul(activeCam->frustum.up).Normalized();
	}

	if (motion_y != 0.f)
	{
		Quat q = Quat::RotateAxisAngle(activeCam->frustum.WorldRight(), motion_y);
		float3 newPos = q.Mul(activeCam->frustum.up).Normalized();

		if (newPos.y > 0.0f)
		{
			activeCam->frustum.up = newPos;
			activeCam->frustum.front = q.Mul(activeCam->frustum.front).Normalized();
		}
	}

	float3 dist = looking_at - activeCam->frustum.pos;
	looking_at = activeCam->frustum.pos + activeCam->frustum.front * dist.Length();
}

void ModuleCamera3D::DrawRay()
{
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glColor4f(Red.r, Red.g, Red.b, Red.a);

	glVertex3f(rayHit.a.x, rayHit.a.y, rayHit.a.z);
	glVertex3f(rayHit.b.x, rayHit.b.y, rayHit.b.z);

	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

float3 ModuleCamera3D::GetPosition() const
{
	return activeCam->frustum.pos;
}

ComponentCamera* ModuleCamera3D::GetActiveCamera()
{
	return activeCam;
}

const Frustum& ModuleCamera3D::GetActiveFrustum() const
{
	return activeCam->frustum;
}

bool ModuleCamera3D::Intersects(const AABB& box) const
{
	return activeCam->Intersect(box);
}

float* ModuleCamera3D::GetView() const
{
	return activeCam->GetView().ptr();
}

float* ModuleCamera3D::GetProjection() const
{
	return activeCam->GetProjection().ptr();
}

bool* ModuleCamera3D::GetProjectionBool() const
{
	return &activeCam->update_frustum;
}

GameObject* ModuleCamera3D::MousePicking() const
{
	GameObject* GO = nullptr;

	ImVec2 mousePos = { (float)App->input->GetMouseX() / (float)App->window->GetWidth() * 2.f - 1.f, -((float)App->input->GetMouseY() / (float)App->window->GetHeight() * 2.f - 1.f) };

	LineSegment ray = activeCam->NearSegment((float)mousePos.x, (float)mousePos.y);

	float distance = 99999999999.f;

	GO = App->scene_intro->MousePicking(ray, distance);

	return GO;
}

bool ModuleCamera3D::CheckMousePosition()
{
	if (isOnConfiguration || isOnConsole || isOnHierarchy || isOnInspector
		|| isOnState || isOnResources || isOnResourcesChild1 || isOnResourcesChild2
		|| isOnQuit || isOnSelectTexture || isOnMainBar)
		return true;

	else if (ImGui::IsAnyItemHovered())
		return true;

	else return false;

}