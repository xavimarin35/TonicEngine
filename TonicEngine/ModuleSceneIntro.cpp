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

	// Uncomment here and on PostUpdate to draw the cube in the second mode (Vertex Array)
	(DrawVertexArrays(1));

	// Uncomment here and on PostUpdate to draw the cube in the third mode (Indices) ----NOT WORKING----
	// DrawIndices(1);

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

	// Uncomment to draw the cube in the first mode (Direct Mode)
	 DrawDirectMode();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	// Uncomment here and on Start to draw the cube in the second mode (Vertex Array)
	 DrawVertexArrays(2);

	// Uncomment here and on Start to draw the cube in the third mode (Indices) ----NOT WORKING----
	// DrawIndices(2); 

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision()
{
}

void ModuleSceneIntro::DrawDirectMode()
{
	glLineWidth(2.0f);

	glBegin(GL_TRIANGLES);

	// Front Face
	glVertex3f(0, 0, 2); // A
	glVertex3f(2, 0, 2); // B
	glVertex3f(0, 2, 2); // C

	glVertex3f(2, 0, 2); // B
	glVertex3f(2, 2, 2); // D
	glVertex3f(0, 2, 2); // C

	// Right Face
	glVertex3f(2, 0, 2); // B
	glVertex3f(2, 0, 0); // F
	glVertex3f(2, 2, 2); // D

	glVertex3f(2, 0, 0); // F
	glVertex3f(2, 2, 0); // H
	glVertex3f(2, 2, 2); // D

	// Behind Face
	glVertex3f(2, 0, 0); // F
	glVertex3f(0, 0, 0); // E
	glVertex3f(2, 2, 0); // H

	glVertex3f(0, 0, 0); // E
	glVertex3f(0, 2, 0); // G
	glVertex3f(2, 2, 0); // H

	// Left Face
	glVertex3f(0, 0, 0); // E
	glVertex3f(0, 0, 2); // A
	glVertex3f(0, 2, 0); // G

	glVertex3f(0, 0, 2); // A
	glVertex3f(0, 2, 2); // C
	glVertex3f(0, 2, 0); // G

	// Up Face
	glVertex3f(0, 2, 2); // C
	glVertex3f(2, 2, 2); // D
	glVertex3f(0, 2, 0); // G

	glVertex3f(2, 2, 2); // D
	glVertex3f(2, 2, 0); // H
	glVertex3f(0, 2, 0); // G

	// Down Face
	glVertex3f(0, 0, 0); // E
	glVertex3f(2, 0, 0); // F
	glVertex3f(0, 0, 2); // A

	glVertex3f(2, 0, 0); // F
	glVertex3f(2, 0, 2); // B
	glVertex3f(0, 0, 2); // A

	glEnd();

	glLineWidth(1.0f);
}

void ModuleSceneIntro::DrawVertexArrays(int stage)
{
	if (stage == 1)
	{
		float Vertices[108] =
		{
			3, 3, 5, // A
			5, 3, 5, // B
			3, 5, 5, // C

			5, 3, 5, // B
			5, 5, 5, // D
			3, 5, 5,// C

			5, 3, 5, // B
			5, 3, 3, // F
			5, 5, 5, // D

			5, 3, 3, // F
			5, 5, 3, // H
			5, 5, 5, // D

			5, 3, 3, // F
			3, 3, 3, // E
			5, 5, 3, // H

			3, 3, 3, // E
			3, 5, 3, // G
			5, 5, 3, // H

			3, 3, 3, // E
			3, 3, 5, // A
			3, 5, 3, // G

			3, 3, 5, // A
			3, 5, 5, // C
			3, 5, 3, // G

			3, 5, 5, // C
			5, 5, 5, // D
			3, 5, 3, // G

			5, 5, 5, // D
			5, 5, 3, // H
			3, 5, 3, // G

			3, 3, 3, // E
			5, 3, 3, // F
			3, 3, 5, // A

			5, 3, 3, // F
			5, 3, 5, // B
			3, 3, 5  // A
		};

		glGenBuffers(1, (GLuint*)&(my_id));

		glBindBuffer(GL_ARRAY_BUFFER, my_id);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, Vertices, GL_STATIC_DRAW);
	}
	
	else if (stage == 2)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, my_id);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

void ModuleSceneIntro::DrawIndices(int stage)
{
	if (stage == 1)
	{
		float Vertices[24] =
		{
			3, 3, 5, // A
			5, 3, 5, // B
			3, 5, 5, // C
			5, 5, 5, // D
			3, 3, 3, // E
			5, 3, 3, // F
			3, 5, 3, // G
			5, 5, 3, // H
		};

		float Indices[36] =
		{
			0,1,2, 2,3,0,
			0,3,4, 4,5,0,
			0,5,6, 6,1,0,

			1,6,7, 7,2,1,
			7,4,3, 3,2,7,
			4,7,6, 6,5,4
		};

		glGenBuffers(1, (GLuint*)&(my_indices));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 36, Indices, GL_STATIC_DRAW);
	}

	if (stage == 2)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	}
}