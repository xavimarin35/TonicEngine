#ifndef __PANELINSPECTOR_H__
#define __PANELINSPECTOR_H__

#include "Application.h"


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
