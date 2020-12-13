#ifndef __PANELGAME_H__
#define __PANELGAME_H__

#include "Application.h"
#include "ModuleGUI.h"
#include "PanelManager.h"

class PanelGame : public PanelManager
{
public:
	PanelGame();
	~PanelGame();

	bool Start();
	bool Draw();
};

#endif