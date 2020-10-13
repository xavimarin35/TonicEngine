#include "Application.h"
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
		App->window->GetWindowSize(w_width, w_height);
		ImGui::SetNextWindowPos(PANELCONFIG_POS, ImGuiCond_Once);
		ImGui::SetNextWindowSize((PANELCONFIG_SIZE), ImGuiCond_Once);

		if (ImGui::Begin("Configuration"), &active, ImGuiWindowFlags_NoBackground)
		{
			if (ImGui::CollapsingHeader("Window"))
			{
				ImGui::SliderInt("Width", &screen.width, 1, 1920);
				ImGui::SliderInt("Height", &screen.height, 1, 1080);
				ImGui::SliderFloat("Brightness", &screen.brightness, 0.0f, 1.0f);

				SDL_SetWindowBrightness(App->window->window, screen.brightness);
				SDL_SetWindowSize(App->window->window, screen.width, screen.height);

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

				/*static int framerateCap = App->getFrameRateCap();
				if (ImGui::SliderInt("MaxFPS", &framerateCap, 1, 120))
					App->setFrameRateCap(framerateCap);*/


				if (vector_fps.size() != 100)
				{
					vector_fps.push_back(App->GetFPS());
					vector_ms.push_back(App->GetMS());
				}
				else
				{
					vector_fps.erase(vector_fps.begin());
					vector_fps.push_back(App->GetFPS());

					vector_ms.erase(vector_ms.begin());
					vector_ms.push_back(App->GetMS());
				}


				ImGui::Text("Framerate %.1f", vector_fps[vector_fps.size() - 1]);
				ImGui::PlotHistogram("##framerate", &vector_fps[0], vector_fps.size(), 0, NULL, 0.0f, 100.0f, ImVec2(310, 100));
				ImGui::Text("Milliseconds %.1f", vector_ms[vector_ms.size() - 1]);
				ImGui::PlotHistogram("##milliseconds", &vector_ms[0], vector_ms.size(), 0, NULL, 0.0f, 40.0f, ImVec2(310, 100));

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

void PanelConfiguration::UpdateFPS(float fps, float ms)
{
	for (uint i = 0; i < HISTOGRAM_BARS - 1; ++i)
	{
		fpsVec[i] = fpsVec[i + 1];
		msVec[i] = msVec[i + 1];
	}

	fpsVec[HISTOGRAM_BARS - 1] = fps;
	msVec[HISTOGRAM_BARS - 1] = ms;
}
