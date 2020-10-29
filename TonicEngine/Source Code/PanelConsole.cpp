#include "PanelConsole.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"

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

		if (ImGui::Begin("Console", &active, ImGuiWindowFlags_NoScrollWithMouse || ImGuiWindowFlags_NoScrollbar)) {

			if (ImGui::IsWindowHovered()) App->camera->isOnScreen = false;
			else App->camera->isOnScreen = true;

			if (ImGui::Button("Clear"))
				EraseLogs();

			ImGui::SameLine();

			// Filter Input
			Filter.Draw("Filter", -100.0f);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			const char* buf = Buf.begin();
			const char* buf_end = Buf.end();
			if (Filter.IsActive())
			{
				for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					if (Filter.PassFilter(line_start, line_end))
						ImGui::TextUnformatted(line_start, line_end);
				}
			}
			else
			{
				ImGuiListClipper clipper;
				clipper.Begin(LineOffsets.Size);
				while (clipper.Step())
				{
					for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
					{
						const char* line_start = buf + LineOffsets[line_no];
						const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
						ImGui::TextUnformatted(line_start, line_end);
					}
				}
				clipper.End();
			}
			ImGui::PopStyleVar();

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 6));

			ImGui::Separator();
			
			for (list<char*>::iterator item = consoleLogs.begin(); item != consoleLogs.end(); ++item)
			{
				ImVec4 color = TEXT_CONSOLE_COLOR;
				bool has_color = true;
				if (strstr((*item), "ERROR:"))
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


