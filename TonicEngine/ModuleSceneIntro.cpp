#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "TextureImporter.h"
#include "ModuleImporter.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "ModuleCamera3D.h"
#include "Math.h"
#include "Component.h"

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
	LOG_IMGUI_CONSOLE("Loading Intro assets");
	LOG_IMGUI_CONSOLE("Loading Scene");

	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));	

	uint Texture = App->tex_imp->LoadTexture("Assets/Baker_house.png");

	App->importer->Load("Assets/BakerHouse.fbx");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG_IMGUI_CONSOLE("Unloading Intro scene");

	for (int i = 0; i < gameobjectsList.size(); ++i)
		delete gameobjectsList[i];

	gameobjectsList.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	for (int i = 0; i < gameobjectsList.size(); ++i)
		gameobjectsList[i]->Update();

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


	for (std::vector<GameObject*>::iterator it = gameobjectsList.begin(); it != gameobjectsList.end(); ++it)
	{
		App->renderer3D->DrawObj((*it)->GetComponent(COMPONENT_TYPE::MESH));
	}

	return UPDATE_CONTINUE;
}

GameObject* ModuleSceneIntro::CreateShape(SHAPE_TYPE type)
{
	return nullptr;
}

GameObject* ModuleSceneIntro::CreateGO()
{
	std::string n = "GO1";
	n.append(std::to_string(gameobjectsList.size()));

	GameObject* GO = new GameObject(n.data());
	GO->oData.id = gameobjectsList.size();

	gameobjectsList.push_back(GO);

	return GO;
}

void ModuleSceneIntro::DestroySelectedGO(GameObject* GO)
{
	if (GOselected == GO)
		GOselected = nullptr;

	for (int i = 0; i < gameobjectsList.size(); ++i)
	{
		if (gameobjectsList[i] == GO)
		{
			gameobjectsList.erase(gameobjectsList.begin() + i);
		}
	}

	delete GO;
}

string ModuleSceneIntro::AssignNameToGO(string name)
{
	nameObj = name.append(std::to_string(gameobjectsList.size()));

	return nameObj;
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
