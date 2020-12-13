#ifndef __PANELMANAGER_H__
#define __PANELMANAGER_H__

#include "Application.h"

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
};

#endif