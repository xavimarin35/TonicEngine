#ifndef __PANELVIEWPORT_H__
#define __PANELVIEWPORT_H__

#include "Application.h"
#include "PanelManager.h"
#include "TextureImporter.h"
#include "ComponentCamera.h"

class PanelViewport
{
public:
	PanelViewport();
	~PanelViewport();

	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	void ChooseCamera(ComponentCamera* camera);
	void PrintTexture(uint tex);
};


#endif
