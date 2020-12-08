#ifndef __PANELRESOURCES_H__
#define __PANELRESOURCES_H__

#include "Application.h"
#include "PanelManager.h"

class PanelResources : public PanelManager
{
public:
	PanelResources();
	~PanelResources();

	bool Start();
	bool Draw();

	bool showing_textures = false;
	bool showing_meshes = false;
};

#endif