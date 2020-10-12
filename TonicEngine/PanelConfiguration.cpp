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
		ImGui::SetNextWindowSize(ImVec2((float)w_width / 4, (float)w_height), ImGuiCond_Once);

		if (ImGui::Begin("Configuration"), &active, ImGuiWindowFlags_AlwaysAutoResize)
		{
			ImGui::SliderInt("Width", &width, 1, 1920);
			ImGui::SliderInt("Height", &height, 1, 1080);
			ImGui::SliderFloat("Brightness", &brightness, 0.0f, 1.0f);

			SDL_SetWindowBrightness(App->window->window, brightness);
			SDL_SetWindowSize(App->window->window, width, height);

			ImGui::Separator();

			if (ImGui::Checkbox("Full Screen", &fullscreen))
				App->window->SetFullScreen(fullscreen);

			if (ImGui::Checkbox("Resizable", &resizable))
				App->window->SetResizable(resizable);

			if (ImGui::Checkbox("Borderless", &borderless))
				App->window->SetBorderless(borderless);
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

		}

		ImGui::End();
	}

	return true;
}
