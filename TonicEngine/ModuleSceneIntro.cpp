#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "TextureImporter.h"
#include "ModuleImporter.h"
#include "Math.h"

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
	App->appLogs.push_back("Loading Intro assets");
	App->appLogs.push_back("Loading Scene");

	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));	

	uint Texture = App->text_imp->LoadTexture("Assets/Baker_house.png");

	App->importer->Load("Assets/BakerHouse.fbx");
	App->importer->meshes.at(0)->texture = Texture;
	App->importer->meshes.at(1)->texture = Texture;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	App->appLogs.push_back("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	//PLANE -----------------------------
	glLineWidth(2.0f);

	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	for (float i = -10; i <= 10; ++i)
	{
		glVertex3f(i, 0.f, 0.f);
		glVertex3f(i, 0, 10.f);

		glVertex3f(0.f, 0.f, i);
		glVertex3f(10.f, 0, i);

		glVertex3f(i, 0.f, 0.f);
		glVertex3f(i, 0, -10.f);

		glVertex3f(0.f, 0.f, i);
		glVertex3f(-10.f, 0, i);
	}
	glEnd();

	// AXIS ------------------------
	glLineWidth(4.0f);

	glBegin(GL_LINES);
	//Y
	glColor3ub(0, 255, 0);
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(0.f, 1.f, 0.f);
	glEnd();

	glBegin(GL_LINES);
	//X
	glColor3ub(255, 0, 0);
	glVertex3f(0.f, 0.001f, 0.f);
	glVertex3f(1.f, 0.001f, 0.f);
	glEnd();

	glBegin(GL_LINES);
	//Z
	glColor3ub(0, 0, 255);
	glVertex3f(0.f, 0.001f, 0.f);
	glVertex3f(0.f, 0.001f, 1.f);
	glEnd();

	glColor3ub(255, 255, 255);

	//Draw meshes
	for (int i = 0; i < App->importer->meshes.size(); ++i)
		App->renderer3D->DrawObj(App->importer->meshes[i]);

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
