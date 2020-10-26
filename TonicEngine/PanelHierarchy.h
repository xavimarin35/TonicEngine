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

private:
};

#endif
