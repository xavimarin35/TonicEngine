#ifndef __PANELINSPECTOR_H__
#define __PANELINSPECTOR_H__

#include "Application.h"
#include "PanelManager.h"

class PanelInspector : public PanelManager
{
public:
	PanelInspector();
	~PanelInspector();

	bool Start();
	bool Draw();

	bool activeGO = true;
};

#endif