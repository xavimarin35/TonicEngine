#ifndef __PANELCONFIGURATION_H__
#define __PANELCONFIGURATION_H__

#include "Application.h"
#include "ModuleGUI.h"
#include "PanelManager.h"

#include <vector>
#include <list>

class Application;

class PanelConfiguration : public PanelManager
{
public:
	PanelConfiguration();
	~PanelConfiguration();

	bool Start();
	bool Draw();

public:
	int		w_width = 0;
	int		w_height = 0;
	
	struct ScreenInfo {
		int		width = SCREEN_WIDTH;
		int		height = SCREEN_HEIGHT;
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
	
public:

	// View Mode
	bool	wireframe = false;
	bool	depth_test = true;
	bool	cull_face = true;
	bool	lighting = true;
	bool	texture2D = true;
	bool	alpha = true;
};

#endif
