#ifndef __PANELSCENE_H__
#define __PANELSCENE_H__

#include "Application.h"
#include "ModuleGUI.h"
#include "PanelManager.h"
#include "Viewport.h"

class PanelScene : public PanelManager
{
public:
	PanelScene();
	~PanelScene();

	bool Start();
	bool Draw();

	ImVec2 current_size = { 1024, 720 };
	ImVec2 new_size;

};

#endif