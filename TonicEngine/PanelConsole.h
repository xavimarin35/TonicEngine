#ifndef __PANELCONSOLE_H__
#define __PANELCONSOLE_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"


class PanelConsole : public PanelManager
{
public:
	PanelConsole();
	~PanelConsole();

	bool Start();
	bool Draw();
};

#endif
