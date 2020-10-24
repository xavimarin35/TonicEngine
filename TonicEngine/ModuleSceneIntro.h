#ifndef __ModuleSceneIntro__
#define __ModuleSceneIntro__

#include "Application.h"
#include "Primitive.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnCollision();

	void DrawCube_36v(float x, float y, float z, float size);

	// DRAW CUBE INFO
	uint id_vertices = 0;
	uint id_no_dup_vertices = 1;
	uint id_indices = 2;

};


#endif __ModuleSceneIntro__