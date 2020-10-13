#ifndef __ModuleSceneIntro__
#define __ModuleSceneIntro__

#include "Module.h"
#include "Globals.h"
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

	void DrawDirectMode();
	void DrawVertexArrays(int stage);
	void DrawIndices(int stage);

private:

	uint my_id = 0;
	uint my_indices = 0;

};


#endif __ModuleSceneIntro__