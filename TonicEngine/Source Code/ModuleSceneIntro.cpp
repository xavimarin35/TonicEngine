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
#include "ModuleResources.h"
#include "ModuleFileSystem.h"

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

	App->camera->Move(float3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(float3(0, 0, 0));	

	Create3DObject(OBJECTS3D::BAKER_HOUSE);

	App->tex_imp->GenerateCheckersTexture();

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG_C("Unloading Intro scene");

	if (GOroot->childrenList.size() > 0)
	{
		for (int i = 0; i < gameobjectsList.size(); ++i)
			delete gameobjectsList[i];
	}

	gameobjectsList.clear();

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	GOroot->Update();

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->gui->saveSceneMenu = true;

	if (App->input->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		App->gui->loadSceneMenu = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		App->gui->exitMenu = true;

	return UPDATE_CONTINUE;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{
	if (drawGrid)
		DrawGridAndAxis(true);
	else
		DrawGridAndAxis(false);


	// Drawing GameObjects (IF CULLING DEACTIVATED)
	if (GOselected != nullptr)
	{
		if (IsCamera(GOselected))
			DrawGameObjectNodes(GOroot);
	}
	else
		DrawGameObjectNodes(GOroot);
	

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::DrawGameObjectNodes(GameObject* GO)
{
	// GO is active and GO is not Root
	if (GO->data.active == true && GO->data.id != 0)
	{
		glPushMatrix();
		glMultMatrixf((GLfloat*)&GO->GetComponentTransform()->GetGlobalTransform().Transposed());
		App->renderer3D->GenerateObject(GO);
		glPopMatrix();
	}

	if (GO->childrenList.size() > 0)
	{
		for (std::vector<GameObject*>::iterator it = GO->childrenList.begin(); it != GO->childrenList.end(); ++it)
		{
			DrawGameObjectNodes(*it);
		}
	}
}

void ModuleSceneIntro::SaveScene(std::string scene_name)
{
	std::string full_path = ASSETS_SCENES_FOLDER + scene_name + ".json";

	SaveGameObjects(App->jsonImp, GOroot);

	std::ofstream stream;
	stream.open(full_path);
	stream << std::setw(4) << App->jsonImp << std::endl;
	stream.close();
}

void ModuleSceneIntro::SaveGameObjects(nlohmann::json& scene, GameObject* GO)
{
	GO->Save(GO->data.id, scene);

	for (int i = 0; i < GO->childrenList.size(); ++i)
		SaveGameObjects(scene, GO->childrenList[i]);
}

void ModuleSceneIntro::DeleteScene()
{
	for (int i = 0; i < GOroot->childrenList.size(); i++)
	{
		GOroot->childrenList[i]->RemoveChild(GOroot->childrenList[i]);
		GOselected = nullptr;
	}

	GOroot->childrenList.clear();
	numGO = 0;
}

void ModuleSceneIntro::LoadScene(std::string scene_name)
{
	//DeleteScene();
	LOG_C("WARNING: Scene has saved correcty, but cannot be loaded yet.");
	LOG_C("WARNING: It will be implemented in upcoming releases.");

	// Loading scene code
}

GameObject* ModuleSceneIntro::CreateGO(string objName, GameObject* parent)
{
	string n = AssignNameToGO(objName, false, false);

	GameObject* GO = new GameObject(n);

	GO->data.id = numGO;
	numGO++;
	gameobjectsList.push_back(GO);

	if (parent != nullptr)
		parent->AddChild(GO);
	
	return GO;
}

GameObject* ModuleSceneIntro::CreateCamera(string objName, GameObject* parent)
{
	string n = AssignNameToGO(objName, true, false);

	GameObject* GO = new GameObject(n);

	GO->CreateComponent(COMPONENT_TYPE::CAMERA);

	GO->data.id = numGO;
	numGO++;
	gameobjectsList.push_back(GO);

	if (parent != nullptr)
		parent->AddChild(GO);

	return GO;
}

GameObject* ModuleSceneIntro::CreateEmpty(string objName, GameObject* parent)
{
	string n = AssignNameToGO(objName, false, true);

	GameObject* GO = new GameObject(n);

	GO->data.id = numGO;
	numGO++;
	gameobjectsList.push_back(GO);

	if (parent != nullptr)
		parent->AddChild(GO);

	return GO;
}

string ModuleSceneIntro::AssignNameToGO(string name_go, bool isCamera, bool isEmpty)
{
	if (isCamera)
	{
		cam_aux = cam_i;
		string cam_name = name_go.append(std::to_string(cam_aux));
		cam_i = cam_aux + 1;
		return cam_name;
	}
	else if (isEmpty)
	{
		empty_aux = empty_i;
		string empty_name = name_go.append(std::to_string(empty_aux));
		empty_i = empty_aux + 1;
		return empty_name;
	}
	else
		return name_go;
}

void ModuleSceneIntro::RemoveSelectedGO(GameObject* GO)
{
	if (GO != GOroot && !gameobjectsList.empty() && GO != nullptr)
	{
		GOselected = nullptr;
		App->gui->Pstate->drawBB = 0;
		GO->data.active = false;

		for (int i = 0; i < gameobjectsList.size(); ++i)
		{
			if (gameobjectsList[i] == GO)
			{
				gameobjectsList.erase(gameobjectsList.begin() + i);
				GO->CleanUp();
				GO = nullptr;
			}
		}		
	}
}

void ModuleSceneIntro::RemoveAllGO()
{
	for (std::vector<GameObject*>::iterator i = GOroot->childrenList.begin(); i != GOroot->childrenList.end(); ++i)
	{
		if ((*i) != nullptr)
		{
			(*i)->data.active = false;
			delete (*i);
			(*i) = nullptr;
		}
	}

	GOselected = nullptr;
	GOroot->childrenList.clear();
}

void ModuleSceneIntro::NumberOfGO()
{
	LOG_C("There are %i GameObjects", gameobjectsList.size());
}

void ModuleSceneIntro::NumberOfComponents()
{
	LOG_C("This GO has %i components", App->scene_intro->GOselected->componentsList.size());
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

bool ModuleSceneIntro::DrawGridAndAxis(bool active)
{
	if (active)
	{
		//PLANE -----------------------------
		glLineWidth(gridWidth);

		glBegin(GL_LINES);
		glColor3f(gridColor.r, gridColor.g, gridColor.b);
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

	case OBJECTS3D::GERALT:
		App->mesh_imp->LoadFile("Assets/Models/Geralt_1.obj", "Assets/Models/Geralt.png");
		break;

	case OBJECTS3D::LIGHTPOST:
		App->mesh_imp->LoadFile("Assets/Models/LightPost_1.obj", "Assets/Models/LightPost.png");
		break;

	case OBJECTS3D::CARRIAGE:
		App->mesh_imp->LoadFile("Assets/Models/Carriage_1.obj", "Assets/Models/Carriage.png");
		break;

	case OBJECTS3D::ROCK:
		App->mesh_imp->LoadFile("Assets/Models/Rock_1.obj", "Assets/Models/Rock.png");
		break;

	case OBJECTS3D::BAKER_HOUSE:
		App->mesh_imp->LoadFile("Assets/Models/BakerHouse_1.obj", "Assets/Models/BakerHouse.png");
		break;

	case OBJECTS3D::STREET:
		App->mesh_imp->LoadFile("Assets/Street/Street_V04.fbx");
		break;
	}
}

bool ModuleSceneIntro::IsCamera(GameObject* go)
{
	bool ret;

	// Selected GO
	if (go != nullptr)
	{
		// GO is a camera
		if (go->GetComponentCamera() != nullptr)
		{
			// Frustum activated
			if (go->GetComponentCamera()->showFrustum)
			{
				ret = false;
			}
			// Frustum deactivated
			else
			{
				ret = true;
			}
		}
		else // GO is not a camera
		{
			ret = true;
		}
	}
	else // if not Selected GO
	{
		ret = true;
	}

	return ret;
}

GameObject* ModuleSceneIntro::MousePicking(const LineSegment& segment, float& distance, bool closest) const
{
	distance = 99999999999.f;

	GameObject* pick = nullptr;

	for (auto it : gameobjectsList)
	{
		if (it->aabb.IsFinite())
		{
			if (segment.Intersects(it->aabb))
			{
				ComponentTransform* transf = (ComponentTransform*)it->GetComponent(COMPONENT_TYPE::TRANSFORM);
				ComponentMesh* mesh = (ComponentMesh*)it->GetComponent(COMPONENT_TYPE::MESH);

				if (mesh != nullptr)
				{
					if (mesh->rMesh->data.vertex != nullptr && mesh->rMesh->data.index != nullptr)
					{
						LineSegment ray(segment);
						ray.Transform(transf->GetGlobalTransform().Inverted());

						Triangle triangle;

						for (uint i = 0; i < mesh->rMesh->data.num_index;)
						{
							triangle.a = mesh->rMesh->data.vertex[mesh->rMesh->data.index[i]]; ++i;
							triangle.b = mesh->rMesh->data.vertex[mesh->rMesh->data.index[i]]; ++i;
							triangle.c = mesh->rMesh->data.vertex[mesh->rMesh->data.index[i]]; ++i;

							float length; float3 hitPos;

							if (ray.Intersects(triangle, &length, &hitPos))
							{
								if (closest && length < distance)
								{
									distance = length;
									pick = (GameObject*)it;
								}
							}
						}
					}
				}
			}
		}		
	}

	return pick;
}