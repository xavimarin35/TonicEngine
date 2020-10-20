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
	App->appLogs.push_back("Loading Scene");

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
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	DrawCube_36v(2, 0, -2, 1);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision()
{
}

void ModuleSceneIntro::DrawCube_36v(float x, float y, float z, float size)
{
	float vertices[] =
	{
		x + 0.f,	 y + size,		z + 0.f,
		x + 0.f,	 y + 0.f,		z + 0.f,
		x + 0.f,	 y + 0.f,		z + size,
		x + 0.f,	 y + size,		z + 0.f,
		x + 0.f,	 y + 0.f,		z + size,
		x + 0.f,	 y + size,		z + size,
		x + 0.f,	 y + size,		z + size,
		x + 0.f,	 y + 0.f,		z + size,
		x + size,	 y + 0.f,		z + size,
		x + 0.f,	 y + size,		z + size,
		x + size,	 y + 0.f,		z + size,
		x + size,	 y + size,		z + size,
		x + 0.f,	 y + size,		z + 0.f,
		x + 0.f,	 y + size,		z + size,
		x + size,	 y + size,		z + size,
		x + 0.f,	 y + size,		z + 0.f,
		x + size,	 y + size,		z + size,
		x + size,	 y + size,		z + 0.f,
		x + size,	 y + 0.f,		z + size,
		x + size,	 y + 0.f,		z + 0.f,
		x + size,	 y + size,		z + 0.f,
		x + size,	 y + size,		z + size,
		x + size,	 y + 0.f,		z + size,
		x + size,	 y + size,		z + 0.f,
		x + size,	 y + 0.f,		z + 0.f,
		x + 0.f,	 y + 0.f,		z + 0.f,
		x + 0.f,	 y + size,		z + 0.f,
		x + size,	 y + size,		z + 0.f,
		x + size,	 y + 0.f,		z + 0.f,
		x + 0.f,	 y + size,		z + 0.f,
		x + size,	 y + 0.f,		z + size,
		x + 0.f,	 y + 0.f,		z + size,
		x + 0.f,	 y + 0.f,		z + 0.f,
		x + size,	 y + 0.f,		z + 0.f,
		x + size,	 y + 0.f,		z + size,
		x + 0.f,	 y + 0.f,		z + 0.f
	};

	glGenBuffers(1, (GLuint*)&(id_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 108, vertices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableClientState(GL_VERTEX_ARRAY);

}
