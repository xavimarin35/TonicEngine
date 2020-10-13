#ifndef __PANELCONFIGURATION_H__
#define __PANELCONFIGURATION_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"

#include <vector>
#include <list>

// Temporal hard-coded until implement Docking 
#define PANELCONFIG_POS ImVec2(1152.0f, 18.0f)
#define PANELCONFIG_SIZE ImVec2((float)w_width / 5, (float)w_height - 18)

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
	
};

#endif
