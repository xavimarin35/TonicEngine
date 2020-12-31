#include "Application.h"
#include "ModuleUserInterface.h"
#include "ModuleGUI.h"
#include "ModuleRenderer3D.h"

ModuleUserInterface::ModuleUserInterface(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUserInterface::~ModuleUserInterface()
{
}

bool ModuleUserInterface::Init()
{
	FT_Error error = FT_Init_FreeType(&ft_library);

	if (error)
	{
		LOG_C("ERROR: Could not init FreeType Library ");
	}

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

void ModuleUserInterface::SetUIRenderSettings()
{
	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ModuleUserInterface::DrawUI()
{
	// GetComponentCamera to set what camera we will be using while rendering elements of the list

	for (auto it = GOcanvas.begin(); it != GOcanvas.end(); it++)
	{
		// we must set the orthogonal cam here (?) and then...

		SetUIRenderSettings();
		(*it)->Draw();
	}
}


