#ifndef __PANELSTATE_H__
#define __PANELSTATE_H__

#include "Application.h"
#include "PanelManager.h"
#include "TextureImporter.h"

class ResourceTexture;

class PanelState : public PanelManager
{
public:
	PanelState();
	~PanelState();

	bool Start();
	bool Draw();
	bool CleanUp();

	void DrawGuizmoButtons();
	void ManageEngineStateButtonsLogic();
	void DrawBBButtons();
	void TimeInfoMenu();
	void LoadButtonsTextures();

	void ToolTipShortCut(const char* word);

	int drawBB = 0;
	bool editing = true;
	float play_time = 0.0f;
	float current_dt = 0.0f;
	bool openTimeMenu = false;

	ResourceTexture* current_tex1 = nullptr;
	ResourceTexture* current_tex2 = nullptr;

	uint currentBut1 = 1; // 1 play, 2 stop
	uint currentBut2 = 3; // 1 pause, 2 resume

public:
	ResourceTexture* move = nullptr;
	ResourceTexture* rot = nullptr;
	ResourceTexture* scale = nullptr;

	ResourceTexture* play = nullptr;
	ResourceTexture* pause = nullptr;
	ResourceTexture* stop = nullptr;
	ResourceTexture* resume = nullptr;

	ResourceTexture* ownBB = nullptr;
	ResourceTexture* allBB = nullptr;

};

#endif