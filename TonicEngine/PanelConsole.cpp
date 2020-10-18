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

		if (ImGui::Begin("Console", &active)) {

			if (ImGui::Button("Clear"))
				EraseLogs();

			ImGui::Separator();

			ImGui::BeginChild("Scroll", ImVec2(0, 200), false, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 6));
			
			for (list<char*>::iterator item = consoleLogs.begin(); item != consoleLogs.end(); ++item)
			{
				ImVec4 color = TEXT_CONSOLE_COLOR;
				bool has_color = true;
				if (strstr((*item), "error:"))
				{
					color = ERROR_CONSOLE_COLOR;
					has_color = true;
				}
				if (has_color)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, color);
					ImGui::TextUnformatted(*item);
					ImGui::PopStyleColor();
				}
			}

			ImGui::PopStyleVar();
			ImGui::EndChild();
		}

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


