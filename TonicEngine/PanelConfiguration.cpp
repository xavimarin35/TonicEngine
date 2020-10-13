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
		App->window->GetWindowSize(screen.w_width, screen.w_height);
		ImGui::SetNextWindowSize(ImVec2((float)screen.w_width / 5, (float)screen.w_height), ImGuiCond_Once);

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
				char name[60];
				strcpy_s(name, 60, App->window->GetTitle());

				if (ImGui::InputText("Engine Name", name, 60, ImGuiInputTextFlags_EnterReturnsTrue))
					App->window->SetTitle(name);

				ImGui::Separator();

				App->gui->max_fps = App->GetFrameRateLimit();
				if (ImGui::SliderInt("Max FPS", &App->gui->max_fps, 0, 200))
					App->SetFrameRateLimit(App->gui->max_fps);

				ImGui::Text("Limit Framerate:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(PanelTextColor), "%d", App->GetFrameRateLimit());
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
				ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", float(hardware.VRAM_budget) / (1024.0f));

				glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &hardware.VRAM_available);
				ImGui::Text("VRAM Available:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", float(hardware.VRAM_usage) / (1024.f));

				hardware.VRAM_usage = hardware.VRAM_budget - hardware.VRAM_available;
				ImGui::Text("VRAM Usage:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(255, 255, 0, 255), "%f", float(hardware.VRAM_available) / (1024.f));

			}

		}

		ImGui::End();
	}

	return true;
}
