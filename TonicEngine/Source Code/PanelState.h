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

	bool editing = true;
	float play_time = 0.0f;

	bool bPlay = true;
	bool bPause = true;
	bool bStop = false;
	bool bResume = false;

public:

	Texture current_tex1;
	Texture current_tex2;

	uint currentBut1 = 1; // 1 play, 2 stop
	uint currentBut2 = 3; // 1 pause, 2 resume

	Texture move;
	Texture rot;
	Texture scale;
	Texture play;
	Texture pause;
	Texture stop;
	Texture resume;
};

#endif
