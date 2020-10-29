#ifndef __PANELABOUT_H__
#define __PANELABOUT_H__

#include "Application.h"
#include "PanelManager.h"


class PanelAbout : public PanelManager
{
public:
	PanelAbout();
	~PanelAbout();

	bool Start();
	bool Draw();
};

#endif