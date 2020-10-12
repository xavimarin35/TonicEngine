#ifndef __PANELHIERARCHY_H__
#define __PANELHIERARCHY_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"


class PanelHierarchy : public PanelManager
{
public:
	PanelHierarchy();
	~PanelHierarchy();

	bool Start();
	bool Draw();
};

#endif
