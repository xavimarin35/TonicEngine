#include "Application.h"
#include "Globals.h"
#include "PanelConfiguration.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"

#include "SDL/include/SDL_opengl.h"
#include "imgui-1.78/imgui_impl_sdl.h"

PanelConfiguration::PanelConfiguration() : PanelManager()
{
	
}

PanelConfiguration::~PanelConfiguration()
{
}

bool PanelConfiguration::Start()
{
	this->active = true;

	return true;
}

bool PanelConfiguration::Draw()
{
	if (!App->gui->Pconfig->active)
		return false;

	if (App->gui->Pconfig->active)
	{
		
		/*ImGui::SetNextWindowPos(PANELCONFIG_POS, ImGuiCond_Once);
		ImGui::SetNextWindowSize((PANELCONFIG_SIZE), ImGuiCond_Once);*/

		if (ImGui::Begin("Configuration", &active))
		{
			if (ImGui::CollapsingHeader("Window"))
			{
				App->window->GetWindowSize(w_width, w_height);
				ImGui::SliderInt("Width", &screen.width, 1, 1440);
				ImGui::SliderInt("Height", &screen.height, 1, 900);
				ImGui::SliderFloat("Brightness", &screen.brightness, 0.0f, 1.0f);

				SDL_SetWindowSize(App->window->window, screen.width, screen.height);
				SDL_SetWindowBrightness(App->window->window, screen.brightness);
				
				ImGui::Separator();

				if (ImGui::Checkbox("Full Screen", &win.fullscreen))
					App->window->SetFullScreen(win.fullscreen);

				if (ImGui::Checkbox("Resizable", &win.resizable))
					App->window->SetResizable(win.resizable);

				if (ImGui::Checkbox("Borderless", &win.borderless))
					App->window->SetBorderless(win.borderless);
			}

			if (ImGui::CollapsingHeader("Application"))
			{
				// App Name
				static char appName[60];
				if (App->GetAppName() != nullptr)
					strcpy_s(appName, 60, App->GetAppName());
				if (ImGui::InputText("App Name", appName, 60, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
					App->ApplyAppName(appName);

				// Organization Name
				static char orgName[60];
				if (App->GetOrgName() != nullptr)
					strcpy_s(orgName, 60, App->GetOrgName());
				if (ImGui::InputText("Organization Name", orgName, 60, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
					App->ApplyOrgName(orgName);

				ImGui::Separator();

				ImGui::SliderInt("Max FPS", &App->framerateCap, 1, 200);

				ImGui::Text("Limit Framerate:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%d", App->framerateCap);

				char title[25];
				sprintf_s(title, 25, "Framerate %.1f", App->fpsVec[App->fpsVec.size() - 1]);
				ImGui::PlotHistogram("##framerate", &App->fpsVec[0], App->fpsVec.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
				sprintf_s(title, 25, "Milliseconds %0.1f", App->msVec[App->msVec.size() - 1]);
				ImGui::PlotHistogram("##milliseconds", &App->msVec[0], App->msVec.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

			}

			if (ImGui::CollapsingHeader("Hardware"))
			{
				ImGui::Text("SDL Version:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

				ImGui::Separator();

				ImGui::Text("CPUs: ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%d", SDL_GetCPUCount());
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "(Cache: %d kb)", SDL_GetCPUCacheLineSize());

				ImGui::Text("System RAM: ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%f Gb", SDL_GetSystemRAM() / 1024.0f);

				ImGui::Text("Caps: "); ImGui::SameLine();
				if (SDL_HasRDTSC)
					ImGui::TextColored(ImVec4(PanelTextColor), "RDTSC"); ImGui::SameLine();
				if (SDL_HasMMX)
					ImGui::TextColored(ImVec4(PanelTextColor), "MMX"); ImGui::SameLine();
				if (SDL_HasSSE)
					ImGui::TextColored(ImVec4(PanelTextColor), "SSE"); ImGui::SameLine();
				if (SDL_HasSSE2)
					ImGui::TextColored(ImVec4(PanelTextColor), "SSE2"); ImGui::SameLine();
				if (SDL_HasSSE3)
					ImGui::TextColored(ImVec4(PanelTextColor), "SSE3"); /*ImGui::SameLine();*/
				if (SDL_HasSSE41)
					ImGui::TextColored(ImVec4(PanelTextColor), "SSE41"); ImGui::SameLine();
				if (SDL_HasSSE42)
					ImGui::TextColored(ImVec4(PanelTextColor), "SSE42"); ImGui::SameLine();
				if (SDL_HasAVX)
					ImGui::TextColored(ImVec4(PanelTextColor), "AVX");

				ImGui::Separator();

				ImGui::Text("GPU: ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%s", glGetString(GL_RENDERER));

				ImGui::Text("Brand: ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%s", glGetString(GL_VENDOR));

				ImGui::Text("Version: ");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%s", glGetString(GL_VERSION));

				glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &hardware.VRAM_budget);
				ImGui::Text("VRAM Budget:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%f", float(hardware.VRAM_budget) / (1024.0f));

				glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &hardware.VRAM_available);
				ImGui::Text("VRAM Available:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%f", float(hardware.VRAM_usage) / (1024.f));

				hardware.VRAM_usage = hardware.VRAM_budget - hardware.VRAM_available;
				ImGui::Text("VRAM Usage:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%f", float(hardware.VRAM_available) / (1024.f));

			}

		}

		ImGui::End();
	}

	return true;
}


