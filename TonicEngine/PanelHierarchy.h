#ifndef __PANELHIERARCHY_H__
#define __PANELHIERARCHY_H__

#include "Application.h"


class PanelHierarchy : public PanelManager
{
public:
	PanelHierarchy();
	~PanelHierarchy();

	bool Start();
	bool Draw();

	uint selectedGO = 0;

private:
};

#endif
