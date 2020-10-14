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
		ImVec4 color = INIT_MODULE_COLOR;

		PrintLogs();

		ImGui::Begin("Console", &active, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		if (ImGui::Button("Clear"))
			EraseLogs();

			ImGui::BeginChild("Scroll", ImVec2(0, 200), false, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 6));

			for (list<char*>::iterator item = consoleLogs.begin(); item != consoleLogs.end(); ++item)
			{
				
				ImGui::PushStyleColor(ImGuiCol_Text, color);
				ImGui::TextColored(color, (*item));
				ImGui::PopStyleColor();
			}

			ImGui::PopStyleVar();
			ImGui::EndChild();


		ImGui::End();
	}
	return true;
}

void PanelConsole::CreateLog(char* info)
{
	consoleLogs.push_back(info);

	if (consoleLogs.size() > maxLogs)
		consoleLogs.pop_front();
}

void PanelConsole::PrintLogs()
{
	for (list<char*>::const_iterator it = App->appLogs.begin(); it != App->appLogs.end(); ++it)
		CreateLog((*it));

	App->appLogs.clear();
}

void PanelConsole::EraseLogs()
{
	consoleLogs.clear();
}


