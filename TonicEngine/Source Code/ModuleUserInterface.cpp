#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleGUI.h"

ModuleUserInterface::ModuleUserInterface(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUserInterface::~ModuleUserInterface()
{
}

bool ModuleUserInterface::Init()
{
	return true;
}

bool ModuleUserInterface::Start()
{
	return true;
}

update_status ModuleUserInterface::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleUserInterface::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleUserInterface::CleanUp()
{
	return true;
}

void ModuleUserInterface::SetOrthogonalCamera()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// args: left, right, bottom, top, near, far
	float left = 0.0f;
	float right = 640.0f;
	float bottom = 480.0f;
	float top = 0.0f;
	float near_plane = 1.0f;
	float far_plane = -1.0f;

	glOrtho(left, right, bottom, top, near_plane, far_plane);
}


