#ifndef __PANELINSPECTOR_H__
#define __PANELINSPECTOR_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"

class PanelInspector : public PanelManager
{
public:
	PanelInspector();
	~PanelInspector();

	bool Start();
	bool Draw();

private:

};

#endif
