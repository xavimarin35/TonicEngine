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
	LOG_C("Loading Intro assets");
	LOG_C("Loading Scene");

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
	LOG_C("Unloading Intro scene");

	for (int i = 0; i < gameobjectsList.size(); ++i)
		delete gameobjectsList[i];

	gameobjectsList.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	for (int i = 0; i < gameobjectsList.size(); ++i)
	{
		if(gameobjectsList[i]->oData.active)
		App->renderer3D->GenerateObject(gameobjectsList[i]);

		gameobjectsList[i]->Update();
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	if (drawGrid)
		DrawGridAndAxis(true);
	else
		DrawGridAndAxis(false);

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
	LOG_C("There are %i GameObjects", gameobjectsList.size());
}

void ModuleSceneIntro::GetGameObjectSelectedIndex(GameObject* GO)
{
	GO = App->scene_intro->GOselected;

	for (int i = 0; i < gameobjectsList.size(); ++i)
	{
		if (gameobjectsList[i] == GO)
		{
			LOG_C("Active GO has the index %i in the list", i);
		}
	}
}

void ModuleSceneIntro::GetSizeOfList()
{
	int size = 0;

	for (int i = 0; i < gameobjectsList.size(); ++i)
	{
		size = gameobjectsList.size();
	}

	LOG_C("There are %i GO in the list", size);
}

bool ModuleSceneIntro::DrawGridAndAxis(bool active)
{
	if (active)
	{
		//PLANE -----------------------------
		glLineWidth(gridWidth);

		glBegin(GL_LINES);
		glColor3f(gridColor.r, gridColor.g, gridColor.g);
		for (float i = -10; i <= 10; ++i)
		{
			glVertex3f(i * gridSize, 0.f, 0.f);
			glVertex3f(i * gridSize, 0, 10.f * gridSize);

			glVertex3f(0.f, 0.f, i * gridSize);
			glVertex3f(10.f * gridSize, 0, i * gridSize);

			glVertex3f(i * gridSize, 0.f, 0.f * gridSize);
			glVertex3f(i * gridSize, 0, -10.f * gridSize);

			glVertex3f(0.f, 0.f, i * gridSize);
			glVertex3f(-10.f * gridSize, 0, i * gridSize);
		}
		glEnd();

		// AXIS ------------------------
		glLineWidth(4.0f);

		glBegin(GL_LINES);
		//Y
		glColor3ub(0, 255, 0);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 1.f * axisLength, 0.f);
		glEnd();

		glBegin(GL_LINES);
		//X
		glColor3ub(255, 0, 0);
		glVertex3f(0.f, 0.001f, 0.f);
		glVertex3f(1.f * axisLength, 0.001f, 0.f);
		glEnd();

		glBegin(GL_LINES);
		//Z
		glColor3ub(0, 0, 255);
		glVertex3f(0.f, 0.001f, 0.f);
		glVertex3f(0.f, 0.001f, 1.f * axisLength);
		glEnd();

		glColor3ub(255, 255, 255);

		return true;
	}
	else {
		return false;
	}
	
}

void ModuleSceneIntro::Create3DObject(OBJECTS3D object)
{
	switch (object)
	{
	case OBJECTS3D::B_SPHERE:
		App->mesh_imp->GenerateMesh("Assets/BasicShapes/bSphere.fbx");
		break;

	case OBJECTS3D::B_CUBE:
		App->mesh_imp->GenerateMesh("Assets/BasicShapes/bCube.fbx");
		break;

	case OBJECTS3D::B_CYLINDER:
		App->mesh_imp->GenerateMesh("Assets/BasicShapes/bCylinder.fbx");
		break;

	case OBJECTS3D::B_CONE:
		App->mesh_imp->GenerateMesh("Assets/BasicShapes/bCone.fbx");
		break;

	case OBJECTS3D::B_TREE:
		App->mesh_imp->GenerateMesh("Assets/OtherMeshes/Tree/Tree_Mesh.fbx");
		break;

	case OBJECTS3D::GERALT:
		App->mesh_imp->GenerateMesh("Assets/OtherMeshes/Geralt/Geralt.obj", 1);
		break;

	case OBJECTS3D::LIGHTPOST:
		App->mesh_imp->GenerateMesh("Assets/OtherMeshes/LightPost/LightPost.obj", 2);
		break;

	case OBJECTS3D::CARRIAGE:
		App->mesh_imp->GenerateMesh("Assets/OtherMeshes/Carriage/Carriage.obj", 3);
		break;

	case OBJECTS3D::ROCK:
		App->mesh_imp->GenerateMesh("Assets/OtherMeshes/Rock/Rock.obj", 4);
		break;

	case OBJECTS3D::BAKER_HOUSE:
		App->mesh_imp->GenerateMesh("Assets/BakerHouse.fbx", 5);
		break;
	}
}

uint ModuleSceneIntro::LoadNewTexture(uint id)
{
	uint texture = -1;

	switch (id)
	{
	case 1:
		texture = App->tex_imp->GenerateTexture("Assets/OtherMeshes/Geralt/Geralt.png");
		break;

	case 2:
		texture = App->tex_imp->GenerateTexture("Assets/OtherMeshes/LightPost/LightPost.png");
		break;

	case 3:
		texture = App->tex_imp->GenerateTexture("Assets/OtherMeshes/Carriage/Carriage.png");
		break;

	case 4:
		texture = App->tex_imp->GenerateTexture("Assets/OtherMeshes/Rock/Rock.png");
		break;

	case 5:
		texture = App->tex_imp->GenerateTexture("Assets/Baker_house.png");
		break;
	}

	return texture;
}