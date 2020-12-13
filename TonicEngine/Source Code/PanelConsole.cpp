#include "PanelConsole.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"

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

		if (ImGui::Begin("Console", &active, ImGuiWindowFlags_NoScrollWithMouse || ImGuiWindowFlags_NoScrollbar)) {

			if (ImGui::Button("Last Log"))
				autoScroll = true;

			ImGui::SameLine();

			if (ImGui::Button("Clear"))
			{
				if (!warningShown)
				{
					LOG_C("WARNING: You have erased all the previous LOGs");
					warningShown = true;
				}

				EraseLogs();
			}				

			ImGui::Separator();

			ImGui::BeginChild("");

			if (ImGui::IsWindowHovered()) App->camera->isOnConsole = true;
			else App->camera->isOnConsole = false;
			
			for (list<char*>::iterator item = consoleLogs.begin(); item != consoleLogs.end(); ++item)
			{
				ImVec4 color = TEXT_CONSOLE_COLOR;
				bool has_color = true;
				if (strstr((*item), "ERROR:"))
				{
					color = ERROR_CONSOLE_COLOR;
					has_color = true;
				}
				if (strstr((*item), "WARNING:"))
				{
					color = WARNING_CONSOLE_COLOR;
					has_color = true;
				}
				if (strstr((*item), "SUCCESS:"))
				{
					color = SUCCESS_CONSOLE_COLOR;
					has_color = true;
				}
				if (strstr((*item), "PLAYMODE:"))
				{
					color = PLAYMODE_CONSOLE_COLOR;
					has_color = true;
				}
				if (has_color)
				{
					ImGui::PushStyleColor(ImGuiCol_Text, color);
					ImGui::TextUnformatted(*item);
					ImGui::PopStyleColor();
				}
			}

			if (autoScroll)
				ImGui::SetScrollHere(1.0f);

			ImGui::EndChild();

			autoScroll = false;
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

	autoScroll = true;
}

void PanelConsole::PrintLogs()
{
	for (list<char*>::const_iterator it = App->appLogs.begin(); it != App->appLogs.end(); ++it)
	{
		CreateLog((*it));
	}
		
	App->appLogs.clear();
}

void PanelConsole::EraseLogs()
{
	consoleLogs.clear();

	autoScroll = true;
}