#ifndef __PANELCONSOLE_H__
#define __PANELCONSOLE_H__

#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "PanelManager.h"

#include <list>

// Colors for console text
#define TEXT_CONSOLE_COLOR ImColor(192,192,192)
#define ERROR_CONSOLE_COLOR ImColor(220,20,60)

class PanelConsole : public PanelManager
{
public:
	PanelConsole();
	~PanelConsole();

	bool Start();
	bool Draw();

private:
	void CreateLog(char* info);
	void PrintLogs();
	void EraseLogs();

	bool consoleEmpty = true;
	int maxLogs = 100;
	
	list<char*> consoleLogs;
};

#endif
