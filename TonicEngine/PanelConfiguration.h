#ifndef __PANELCONFIGURATION_H__
#define __PANELCONFIGURATION_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"

#include <list>

class PanelConfiguration : public PanelManager
{
public:
	PanelConfiguration();
	~PanelConfiguration();

	bool Start();
	bool Draw();

public:
	
	
};

#endif
