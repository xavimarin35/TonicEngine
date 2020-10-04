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
	bool CleanUp();

	void OnCollision();

};


#endif __ModuleSceneIntro__