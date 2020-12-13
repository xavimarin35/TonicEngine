#ifndef __ModuleSceneIntro__
#define __ModuleSceneIntro__

#include "Globals.h"
#include "Primitive.h"
#include "GameObject.h"
#include "imgui-1.78/ImGuizmo.h"

enum class OBJECTS3D
{
	NONE = -1,
	B_SPHERE,
	B_CUBE,
	B_CYLINDER,
	B_CONE,
	LIGHTPOST, 
	CARRIAGE, 
	GERALT,
	ROCK,
	BAKER_HOUSE,
	STREET
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Init();
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool DrawGridAndAxis(bool active);
	void Create3DObject(OBJECTS3D object);

	// DRAW CUBE INFO
	uint id_vertices = 0;
	uint id_no_dup_vertices = 1;
	uint id_indices = 2;

	bool IsCamera(GameObject* go);
	GameObject* MousePicking(const LineSegment& segment, float& distance, bool closest = true) const;

	GameObject* CreateGO(string objName, GameObject* parent = nullptr);
	GameObject* CreateCamera(string objName, GameObject* parent = nullptr);
	GameObject* CreateEmpty(string objName, GameObject* parent = nullptr);
	string AssignNameToGO(string name_go, bool isCamera, bool isEmpty);
	void RemoveSelectedGO(GameObject* GO);
	void RemoveAllGO();
	void NumberOfGO();
	void NumberOfComponents();
	void GetGameObjectSelectedIndex(GameObject* GO);
	std::vector<GameObject*> gameobjectsList;

	int cam_i = 0;
	int cam_aux = 0;
	int empty_i = 0;
	int empty_aux = 0;

	void DrawGameObjectNodes(GameObject* GO);
	GameObject* GOselected = nullptr;
	GameObject* GOroot = nullptr;
	uint numGO = 0;

	// Serialization
	void SaveScene(std::string scene_name);
	void SaveGameObjects(nlohmann::json& scene, GameObject* Root);
	void DeleteScene();
	void LoadScene(std::string scene_name);
	int numScene = 0;
	int maxScenes = 25;

	uint texture = -1;

	bool drawGrid = true;
	Color gridColor = White;
	Color bbColor = Blue;
	float bbSize = 1.0f;
	float gridSize = 3.0f;
	float gridWidth = 0.5f;
	float axisLength = 6.0f;

};

#endif __ModuleSceneIntro__