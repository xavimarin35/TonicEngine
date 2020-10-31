#ifndef __ModuleSceneIntro__
#define __ModuleSceneIntro__

#include "Globals.h"
#include "Primitive.h"
#include "GameObject.h"

enum class OBJECTS3D
{
	NONE = -1,
	B_SPHERE,
	B_CUBE,
	B_CYLINDER,
	B_CONE,
	B_TREE,
	LIGHTPOST, 
	CARRIAGE, 
	GERALT,
	ROCK,
	BAKER_HOUSE
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	bool DrawGridAndAxis(bool active);
	void Create3DObject(OBJECTS3D object);
	uint LoadNewTexture(uint id);

	// DRAW CUBE INFO
	uint id_vertices = 0;
	uint id_no_dup_vertices = 1;
	uint id_indices = 2;

	GameObject* CreateGO(string objName);
	string AssignNameToGO(string name_go);
	void RemoveSelectedGO(GameObject* GO);
	void RemoveAllGO();
	void NumberOfGO();
	std::vector<GameObject*> gameobjectsList;

	GameObject* GOselected = nullptr;

	uint texture = -1;

	bool drawGrid = true;
	Color gridColor = White;
	float gridSize = 1.0f;
	float gridWidth = 1.0f;
	float axisLength = 1.0f;
};

#endif __ModuleSceneIntro__