#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__

#include "Globals.h"
#include "Module.h"

#include "imgui-1.78/imgui.h"

#include "imgui-1.78/examples/imgui_impl_sdl.h"
#include "imgui-1.78/examples/imgui_impl_opengl3.h"

#include "glew/include/GL/glew.h"


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
	bool CleanUp();
	void Render();
	
	update_status Update(float dt);
	int rand = 0;
	bool getRand = false;

private:
	ImGuiIO* io = nullptr;

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_close_app_window = true;
	bool show_custom_window = false;

};

#endif // !__MODULEGUI_H__

