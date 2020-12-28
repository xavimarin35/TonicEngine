#ifndef _MODULE_USERINTERFACE_H_
#define _MODULE_USERINTERFACE_H_

#include "Module.h"

class ModuleUserInterface : public Module
{
public:
	ModuleUserInterface(Application* app, bool start_enabled = true);
	~ModuleUserInterface();

	bool Init();
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:


};

#endif
