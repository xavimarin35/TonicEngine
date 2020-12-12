#ifndef __PANELRESOURCES_H__
#define __PANELRESOURCES_H__

#include "Application.h"
#include "PanelManager.h"

class ResourceTexture;

class PanelResources : public PanelManager
{
public:
	PanelResources();
	~PanelResources();

	bool Start();
	bool Draw();

	bool showing_textures = false;
	bool showing_meshes = false;
	bool showing_models = false;

	ResourceTexture* folder = nullptr;
	ResourceTexture* mesh = nullptr;
	ResourceTexture* model = nullptr;
};

#endif