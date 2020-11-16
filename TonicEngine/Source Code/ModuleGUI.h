#ifndef __MODULEGUI_H__
#define __MODULEGUI_H__

#include "PanelManager.h"

#include "imgui-1.78/imgui.h"
#include "SDL/include/SDL_events.h"

#include "imgui-1.78/imgui_impl_sdl.h"
#include "imgui-1.78/imgui_impl_opengl3.h"

#include "glew/include/GL/glew.h"

#include "PanelConfiguration.h"
#include "PanelAbout.h"
#include "PanelConsole.h"
#include "PanelHierarchy.h"
#include "PanelInspector.h"
#include "PanelState.h"

class PanelConfiguration;
class PanelAbout;
class PanelConsole;
class PanelHierarchy;
class PanelInspector;
class PanelState;

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
	
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	void EnableInput(SDL_Event* event);
	void PushBackPanels();
	void ApplyDocking(bool* window);

	// Console
	void LogConsole(char* text, ...);
	static char* Strdup(const char* str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }
	
	PanelConfiguration* Pconfig = nullptr;
	PanelAbout* Pabout = nullptr;
	PanelConsole* Pconsole = nullptr;
	PanelHierarchy* Phierarchy = nullptr;
	PanelInspector* Pinspector = nullptr;
	PanelState* Pstate = nullptr;

	// Random Number Generator 
	int rand = 0;
	bool getRand = false;

	bool saveSceneMenu = false;
	bool loadSceneMenu = false;
	bool exitMenu = false;
	bool deleteScene = false;

	static void HelpMarker(const char* desc);

private:

	ImGuiIO* io = nullptr;
	ImGuiIO* docking_io = nullptr;
	bool* windowDocking;
	bool p_open = true;

	bool show_demo_window = false;
	bool show_style_editor = false;
	
	list<PanelManager*> panels;

};

#endif // !__MODULEGUI_H__

