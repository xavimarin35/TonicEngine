#ifndef __PANELCONSOLE_H__
#define __PANELCONSOLE_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"

#include <list>

class PanelConsole : public PanelManager
{
public:
	PanelConsole();
	~PanelConsole();

	bool Start();
	bool Draw();

private:
	void CreateLog(string info);
	void PrintLogs();
	void EraseLogs();

	bool consoleEmpty = true;
	int maxLogs = 100;
	
	list<string> consoleLogs;
};

#endif
