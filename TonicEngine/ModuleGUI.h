#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__


#include "Globals.h"
#include "Module.h"

#include "imgui-1.78/imgui.h"
#include "imgui-1.78/examples/imgui_impl_sdl.h"
#include "imgui-1.78/examples/imgui_impl_opengl3.h"

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