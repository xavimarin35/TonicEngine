#ifndef __PANELHIERARCHY_H__
#define __PANELHIERARCHY_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"

#define PANELHIERARCHY_POS ImVec2(0, 18)
#define PANELHIERARCHY_SIZE ImVec2((float)w_width / 7, (float)w_height - 18)

class PanelHierarchy : public PanelManager
{
public:
	PanelHierarchy();
	~PanelHierarchy();

	bool Start();
	bool Draw();

private:
	int		w_width = 0;
	int		w_height = 0;
};

#endif
