#ifndef __PANELCONFIGURATION_H__
#define __PANELCONFIGURATION_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"


class PanelConfiguration : public PanelManager
{
public:
	PanelConfiguration();
	~PanelConfiguration();

	bool Start();
	bool Draw();

public:
	int		width = SCREEN_WIDTH;
	int		height = SCREEN_HEIGHT;
	int		w_width = 0;
	int		w_height = 0;
	float	brightness = 1.0f;

	bool	fullscreen = false;
	bool	fulldesktop = false;
	bool	borderless = false;
	bool	resizable = true;

	
};

#endif
