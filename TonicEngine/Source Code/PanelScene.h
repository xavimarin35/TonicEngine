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
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	bool Draw();

	Viewport* viewport_tex = nullptr;
	ImVec2 current_size = { 1024, 720 };
	ImVec2 new_size;

};

#endif