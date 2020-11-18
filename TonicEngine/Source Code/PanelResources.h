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
};

#endif