#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	DrawVertexs();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision()
{
}

void ModuleSceneIntro::DrawVertexs()
{
	glLineWidth(2.0f);

	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 2); // A
	glVertex3f(2, 0, 2); // B
	glVertex3f(0, 2, 2); // C

	glVertex3f(2, 0, 2); // B
	glVertex3f(2, 2, 2); // D
	glVertex3f(0, 2, 2); // C

	glVertex3f(2, 0, 2); // B
	glVertex3f(2, 0, 0); // F
	glVertex3f(2, 2, 2); // D

	glVertex3f(2, 0, 0); // F
	glVertex3f(2, 2, 0); // H
	glVertex3f(2, 2, 2); // D

	glVertex3f(2, 0, 0); // F
	glVertex3f(0, 0, 0); // E
	glVertex3f(2, 2, 0); // H

	glVertex3f(0, 0, 0); // E
	glVertex3f(0, 2, 0); // G
	glVertex3f(2, 2, 0); // H

	glVertex3f(0, 0, 0); // E
	glVertex3f(0, 0, 2); // A
	glVertex3f(0, 2, 0); // G

	glVertex3f(0, 0, 2); // A
	glVertex3f(0, 2, 2); // C
	glVertex3f(0, 2, 0); // G

	glVertex3f(0, 2, 2); // C
	glVertex3f(2, 2, 2); // D
	glVertex3f(0, 2, 0); // G

	glVertex3f(2, 2, 2); // D
	glVertex3f(2, 2, 0); // H
	glVertex3f(0, 2, 0); // G

	glVertex3f(0, 0, 0); // E
	glVertex3f(2, 0, 0); // F
	glVertex3f(0, 0, 2); // A

	glVertex3f(2, 0, 0); // F
	glVertex3f(2, 0, 2); // B
	glVertex3f(0, 0, 2); // A

	glEnd();

	glLineWidth(1.0f);
}