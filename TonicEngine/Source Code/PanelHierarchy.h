#ifndef __PANELHIERARCHY_H__
#define __PANELHIERARCHY_H__

#include "Application.h"
#include "PanelManager.h"


class PanelHierarchy : public PanelManager
{
public:
	PanelHierarchy();
	~PanelHierarchy();

	bool Start();
	bool Draw();
	void DrawMenuHovering();
	void DrawMenuNotHovering();

	bool openMenuHovering = false;
	bool openMenuNotHovering = false;

	uint clickedGO = -1;

private:
};

#endif
