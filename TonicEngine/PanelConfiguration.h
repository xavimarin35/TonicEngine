#ifndef __PANELCONFIGURATION_H__
#define __PANELCONFIGURATION_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"

class Application;

class PanelConfiguration : public PanelManager
{
public:
	PanelConfiguration();
	~PanelConfiguration();

	bool Start();
	bool Draw();

	Application* App;
};

#endif
