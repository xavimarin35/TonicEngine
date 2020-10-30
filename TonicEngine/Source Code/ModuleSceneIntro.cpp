#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "TextureImporter.h"
#include "MeshImporter.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "ModuleCamera3D.h"
#include "Math.h"
#include "Component.h"
#include "ComponentTexture.h"

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

	

	App->mesh_imp->GenerateMesh("Assets/BakerHouse.fbx");

	texture = App->tex_imp->GenerateTexture("Assets/Baker_house.png");

	App->tex_imp->GenerateCheckersTexture();

	gameobjectsList.at(0)->GetComponentTexture()->texture = texture;
	gameobjectsList.at(1)->GetComponentTexture()->texture = texture;

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

	for (std::vector<GameObject*>::iterator it = gameobjectsList.begin(); it != gameobjectsList.end(); ++it)
	{
		if ((*it)->oData.active)
		{
			App->renderer3D->GenerateObject((*it));
		}
	}
	for (int i = 0; i < gameobjectsList.size(); ++i)
	{
		gameobjectsList[i]->Update();
	}


	
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	DrawGridAndAxis();



	return UPDATE_CONTINUE;
}

GameObject* ModuleSceneIntro::CreateGO(string objName)
{
	string n = AssignNameToGO(objName);

	GameObject* GO = new GameObject(n);
	GO->oData.GOid = gameobjectsList.size();

	gameobjectsList.push_back(GO);

	return GO;
}

string ModuleSceneIntro::AssignNameToGO(string name_go)
{
	string name = name_go.append(std::to_string(gameobjectsList.size()));

	return name;
}

void ModuleSceneIntro::RemoveSelectedGO(GameObject* GO)
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

void ModuleSceneIntro::RemoveAllGO()
{
	for (int i = 0; i < gameobjectsList.size(); ++i)
	{
		if(GOselected != nullptr)
		gameobjectsList.erase(gameobjectsList.begin() + i);
	}

	gameobjectsList.clear();
}

void ModuleSceneIntro::NumberOfGO()
{
	LOG_IMGUI_CONSOLE("There are %i GameObjects", gameobjectsList.size());
}

void ModuleSceneIntro::DrawGridAndAxis()
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
}
