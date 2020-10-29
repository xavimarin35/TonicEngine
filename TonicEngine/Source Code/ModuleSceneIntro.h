#ifndef __ModuleSceneIntro__
#define __ModuleSceneIntro__

#include "Globals.h"
#include "Primitive.h"
#include "GameObject.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void DrawGridAndAxis();

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
	uint GOselectedID = 0;

	uint texture;
	uint checkers_texture;
	
};


#endif __ModuleSceneIntro__