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

	void DoButtonFunction(int function);
	void LoadStreet();
	void ChangeVsync();

public:
	ImVec2 size = { 0,0 };
	ImVec2 viewSize = { 0,0 };
	bool resizedLastFrame = false;
	float lastAR = 0;

	bool continued = false;

	GameObject* vsyncBut = nullptr;
};

#endif