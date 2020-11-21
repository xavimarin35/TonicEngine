#ifndef __PANELSTATE_H__
#define __PANELSTATE_H__

#include "Application.h"
#include "PanelManager.h"
#include "TextureImporter.h"

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

	void ToolTipShortCut(const char* word);

	bool drawOwnBB = false;
	bool editing = true;
	float play_time = 0.0f;
	bool openTimeMenu = false;

	Texture current_tex1;
	Texture current_tex2;

	uint currentBut1 = 1; // 1 play, 2 stop
	uint currentBut2 = 3; // 1 pause, 2 resume

public:
	Texture move;
	Texture rot;
	Texture scale;

	Texture play;
	Texture pause;
	Texture stop;
	Texture resume;

	Texture ownBB;
	Texture allBB;

};

#endif
