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
	ENGINE_STATE state = ENGINE_STATE::NONE;
	Texture current_tex1;
	Texture current_tex2;

	Texture move;
	Texture rot;
	Texture scale;
	Texture play;
	Texture pause;
	Texture stop;
	Texture resume;
};

#endif
