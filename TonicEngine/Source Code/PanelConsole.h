#ifndef __PANELCONSOLE_H__
#define __PANELCONSOLE_H__

#include "Application.h"
#include "ModuleGUI.h"
#include "PanelManager.h"

#include <list>

// Colors for console text
#define TEXT_CONSOLE_COLOR ImColor(192,192,192)
#define ERROR_CONSOLE_COLOR ImColor(220,20,60)
#define WARNING_CONSOLE_COLOR ImColor(255,255,0)
#define SUCCESS_CONSOLE_COLOR ImColor(0,255,0)
#define PLAYMODE_CONSOLE_COLOR ImColor(0,255,255)

#define LOG_C(text, ...) App->gui->LogConsole(text, __VA_ARGS__); 

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

	bool autoScroll = false;
	bool warningShown = false;
	bool consoleEmpty = true;
	int maxLogs = 100;

	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets;
	
	list<char*> consoleLogs;
};

#endif
