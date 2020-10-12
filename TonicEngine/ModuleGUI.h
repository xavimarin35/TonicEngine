#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__

#include "Globals.h"
#include "Module.h"
#include "PanelManager.h"

#include "imgui-1.78/imgui.h"

#include "imgui-1.78/examples/imgui_impl_sdl.h"
#include "imgui-1.78/examples/imgui_impl_opengl3.h"

#include "glew/include/GL/glew.h"

#include "PanelConfiguration.h"


class PanelConfiguration;


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
	bool Draw();
	update_status MainMenuBar();
	
	update_status PreUpdate(float dt);
	/*update_status Update(float dt);*/
	update_status PostUpdate(float dt);
	/*update_status Update(float dt);*/
	int rand = 0;
	bool getRand = false;

	// Visible Panels
	bool aboutPanel_visible = false;
	bool configPanel_visible = true;
	bool hardwarePanel_visible = false;

	PanelConfiguration* Pconfig = nullptr;

private:
	ImGuiIO* io = nullptr;

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_close_app_window = true;
	bool show_custom_window = false;

	list<PanelManager*> panels;

};

#endif // !__MODULEGUI_H__

