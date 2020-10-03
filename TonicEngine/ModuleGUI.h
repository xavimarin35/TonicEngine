#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__


#include "Globals.h"
#include "Module.h"


class ModuleGUI : public Module
{
public:
	// CONSTRUCTOR
	ModuleGUI(Application* app, bool start_enabled = true);
	//DESTRUCTOR
	~ModuleGUI();

public:
	bool Init();
	bool Start();
	update_status Update(float dt);

};

#endif // !__MODULEENGINEGUI_H__