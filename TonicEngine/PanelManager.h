#ifndef __PANELMANAGER_H__
#define __PANELMANAGER_H__

#include "Globals.h"
#include "Application.h"
#include "Module.h"

#include "glew/include/GL/glew.h"

#include <list>

class PanelManager
{
public:

	PanelManager(){}
	virtual ~PanelManager(){}

	bool active = false;

	virtual bool Start() { return true; }
	virtual update_status PreUpdate(float dt) { return UPDATE_CONTINUE; }
	virtual update_status Update(float dt) { return UPDATE_CONTINUE; }
	virtual update_status PostUpdate(float dt) { return UPDATE_CONTINUE; }
	virtual bool CleanUp() { return true; }

	virtual bool Draw() { return true; }

	struct ScreenInfo {
		int		width = SCREEN_WIDTH;
		int		height = SCREEN_HEIGHT;
		int		w_width = 0;
		int		w_height = 0;
		float	brightness = 1.0f;
	}screen;


	struct WindowInfo {
		bool	fullscreen = false;
		bool	fulldesktop = false;
		bool	borderless = false;
		bool	resizable = true;
	}win;

	struct HardwareInfo {
		GLint VRAM_budget = 0;
		GLint VRAM_available = 0;
		GLint VRAM_usage = 0;
	}hardware;

};

#endif