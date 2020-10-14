#include "PanelConsole.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"

#include "SDL/include/SDL_opengl.h"
#include "imgui-1.78/imgui_impl_sdl.h"

PanelConsole::PanelConsole() : PanelManager()
{
}

PanelConsole::~PanelConsole()
{
}

bool PanelConsole::Start()
{
	this->active = true;
	
	if (consoleEmpty)
		EraseLogs();

	return true;
}

bool PanelConsole::Draw()
{
	if (!App->gui->Pconsole->active)
		return false;

	if (App->gui->Pconsole->active)
	{
		PrintLogs();

		ImGui::Begin("Console", &active, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		ImGui::End();
	}
	return true;
}

void PanelConsole::CreateLog(string info)
{
	consoleLogs.push_back(info);

	if (consoleLogs.size() > maxLogs)
		consoleLogs.pop_front();
}

void PanelConsole::PrintLogs()
{
	for (list<string>::const_iterator it = App->appLogs.begin(); it != App->appLogs.end(); ++it)
		CreateLog((*it));

	App->appLogs.clear();
}

void PanelConsole::EraseLogs()
{
	consoleLogs.clear();
}


