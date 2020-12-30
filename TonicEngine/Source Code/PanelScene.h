#ifndef __PANELSCENE_H__
#define __PANELSCENE_H__

#include "Application.h"
#include "ModuleGUI.h"
#include "PanelManager.h"

class PanelScene : public PanelManager
{
public:
	PanelScene();
	~PanelScene();

	bool Start();
	bool Draw();

public:
	ImVec2 size = { 0,0 };
	bool resizedLastFrame = false;

};

#endif