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

bool ModuleSceneIntro::Init()
{
	bool ret = true;

	GOroot = CreateGO("Root");

	return ret;
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG_C("Loading Intro assets");
	LOG_C("Loading Scene");

	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));	

	Create3DObject(OBJECTS3D::BAKER_HOUSE);

	App->tex_imp->GenerateCheckersTexture();

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
	
	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	if (drawGrid)
		DrawGridAndAxis(true);
	else
		DrawGridAndAxis(false);

	DrawGameObjectNodes(GOroot);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::DrawGameObjectNodes(GameObject* GO)
{
	// GO is active and GO is not Root
	if (GO->data.active == true && GO->data.id != 0)
	{
		App->renderer3D->GenerateObject(GO);
	}

	if (GO->childrenList.size() > 0)
	{
		for (std::vector<GameObject*>::iterator it = GO->childrenList.begin(); it != GO->childrenList.end(); ++it)
		{
			DrawGameObjectNodes(*it);
		}
	}
}

GameObject* ModuleSceneIntro::CreateGO(string objName, GameObject* parent)
{
	string n = AssignNameToGO(objName);

	GameObject* GO = new GameObject(n);

	GO->data.id = numGO;
	numGO++;
	gameobjectsList.push_back(GO);

	if (parent != nullptr)
		parent->AddChild(GO);
	
	return GO;
}


string ModuleSceneIntro::AssignNameToGO(string name_go)
{
	//string name = name_go.append(std::to_string(numGO));

	return name_go;
}

void ModuleSceneIntro::RemoveSelectedGO(GameObject* GO)
{
	/*if (GO->GOparent != nullptr && isParent == true)
		GO->GOparent->RemoveChild(GO);

	if (GO->childrenList.size() > 0)
	{
		for (std::vector<GameObject*>::iterator it = GO->childrenList.begin(); it != GO->childrenList.end(); ++it)
		{
			RemoveSelectedGO(*it, false);
		}

		GO->childrenList.clear();
	}

	GO->CleanUp();
	delete GO;*/

	if (!gameobjectsList.empty() && GO != nullptr)
	{
		for (int i = 0; i < gameobjectsList.size(); ++i)
		{
			if (gameobjectsList[i] == GO)
			{
				gameobjectsList.erase(gameobjectsList.begin() + i);
				GO->CleanUp();
			}
		}		
	}
	else
	{
		LOG_C("ERROR: GameObject named '%s' wasn't found in the list, so was impossible to delete it", GO->data.name.c_str());
	}
}

// old
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

	LOG_C("The size of the GOs list is %i", size);
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
		App->mesh_imp->LoadFile("Assets/BasicShapes/bSphere.fbx");
		break;

	case OBJECTS3D::B_CUBE:
		App->mesh_imp->LoadFile("Assets/BasicShapes/bCube.fbx");
		break;

	case OBJECTS3D::B_CYLINDER:
		App->mesh_imp->LoadFile("Assets/BasicShapes/bCylinder.fbx");
		break;

	case OBJECTS3D::B_CONE:
		App->mesh_imp->LoadFile("Assets/BasicShapes/bCone.fbx");
		break;

	case OBJECTS3D::B_TREE:
		App->mesh_imp->LoadFile("Assets/OtherMeshes/Tree/Tree_Mesh.fbx", "Assets/OtherMeshes/Tree/Tree_Trunk.png");
		break;

	case OBJECTS3D::GERALT:
		App->mesh_imp->LoadFile("Assets/OtherMeshes/Geralt/Geralt.obj", "Assets/OtherMeshes/Geralt/Geralt.png");
		break;

	case OBJECTS3D::LIGHTPOST:
		App->mesh_imp->LoadFile("Assets/OtherMeshes/LightPost/LightPost.obj", "Assets/OtherMeshes/LightPost/LightPost.png");
		break;

	case OBJECTS3D::CARRIAGE:
		App->mesh_imp->LoadFile("Assets/OtherMeshes/Carriage/Carriage.obj", "Assets/OtherMeshes/Carriage/Carriage.png");
		break;

	case OBJECTS3D::ROCK:
		App->mesh_imp->LoadFile("Assets/OtherMeshes/Rock/Rock.obj", "Assets/OtherMeshes/Rock/Rock.png");
		break;

	case OBJECTS3D::BAKER_HOUSE:
		App->mesh_imp->LoadFile("Assets/BakerHouse/BakerHouse.fbx", "Assets/BakerHouse/Baker_house.png");
		break;

	case OBJECTS3D::STREET:
		App->mesh_imp->LoadFile("Assets/Street/street2.fbx");
		//App->mesh_imp->LoadFile("Assets/Street/street2.FBX");
		break;
	}
}