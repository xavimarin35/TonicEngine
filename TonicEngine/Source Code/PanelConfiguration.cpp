#include "Globals.h"
#include "PanelConfiguration.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleSceneIntro.h"

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

		if (ImGui::Begin("Configuration", &active))
		{
			if (ImGui::IsWindowHovered()) App->camera->isOnConfiguration = true;
			else App->camera->isOnConfiguration = false;

			if (ImGui::CollapsingHeader("Window"))
			{
				ImGui::Spacing();

				App->window->GetWindowSize(w_width, w_height);
				ImGui::DragInt("Width", &screen.width, 1, 1920);
				ImGui::DragInt("Height", &screen.height, 1, 1080);
				ImGui::SliderFloat("Brightness", &screen.brightness, 0.0f, 1.0f);

				SDL_SetWindowSize(App->window->window, screen.width, screen.height);

				SDL_SetWindowBrightness(App->window->window, screen.brightness);
				
				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::Checkbox("Full Screen", &win.fullscreen))
					App->window->SetFullScreen(win.fullscreen);
				ImGui::SameLine();
				if (ImGui::Checkbox("Resizable", &win.resizable))
					App->window->SetResizable(win.resizable);
				ImGui::SameLine();
				if (ImGui::Checkbox("Borderless", &win.borderless))
					App->window->SetBorderless(win.borderless);

				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Application"))
			{
				ImGui::Spacing();

				ImGui::Text("Engine Name: %s", App->appName.c_str());

				// App Name
				static char appName[60];
				if (App->GetAppName() != nullptr)
					strcpy_s(appName, 60, App->GetAppName());
				if (ImGui::InputText("App Name", appName, 60, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
					App->ApplyAppName(appName);

				ImGui::Spacing();
				ImGui::Separator();
				ImGui::Spacing();

				ImGui::SliderInt("Max FPS", &App->framerateCap, 1, 60);

				ImGui::Spacing();

				ImGui::Text("Limit Framerate:");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%d", App->framerateCap);

				ImGui::Spacing();

				char title[25];
				sprintf_s(title, 25, "Framerate %.1f", App->fpsVec[App->fpsVec.size() - 1]);
				ImGui::PlotHistogram("##framerate", &App->fpsVec[0], App->fpsVec.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
				sprintf_s(title, 25, "Milliseconds %0.1f", App->msVec[App->msVec.size() - 1]);
				ImGui::PlotHistogram("##milliseconds", &App->msVec[0], App->msVec.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Hardware"))
			{
				ImGui::Spacing();

				ImGui::Text("SDL Version:");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

				ImGui::Separator();

				ImGui::Text("CPUs: ");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%d", SDL_GetCPUCount());
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "(Cache: %d kb)", SDL_GetCPUCacheLineSize());

				ImGui::Text("System RAM: ");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%f Gb", SDL_GetSystemRAM() / 1024.0f);

				ImGui::Text("Caps: "); ImGui::SameLine();
				if (SDL_HasRDTSC)
					ImGui::TextColored(YELLOW_COLOR, "RDTSC"); ImGui::SameLine();
				if (SDL_HasMMX)
					ImGui::TextColored(YELLOW_COLOR, "MMX"); ImGui::SameLine();
				if (SDL_HasSSE)
					ImGui::TextColored(YELLOW_COLOR, "SSE"); ImGui::SameLine();
				if (SDL_HasSSE2)
					ImGui::TextColored(YELLOW_COLOR, "SSE2"); ImGui::SameLine();
				if (SDL_HasSSE3)
					ImGui::TextColored(YELLOW_COLOR, "SSE3");
				if (SDL_HasSSE41)
					ImGui::TextColored(YELLOW_COLOR, "SSE41"); ImGui::SameLine();
				if (SDL_HasSSE42)
					ImGui::TextColored(YELLOW_COLOR, "SSE42"); ImGui::SameLine();
				if (SDL_HasAVX)
					ImGui::TextColored(YELLOW_COLOR, "AVX");

				ImGui::Separator();

				ImGui::Text("GPU: ");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%s", glGetString(GL_RENDERER));

				ImGui::Text("Brand: ");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%s", glGetString(GL_VENDOR));

				ImGui::Text("Version: ");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%s", glGetString(GL_VERSION));

				glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &hardware.VRAM_budget);
				ImGui::Text("VRAM Budget:");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%f", float(hardware.VRAM_budget) / (1024.0f));

				glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &hardware.VRAM_available);
				ImGui::Text("VRAM Available:");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%f", float(hardware.VRAM_usage) / (1024.f));

				hardware.VRAM_usage = hardware.VRAM_budget - hardware.VRAM_available;
				ImGui::Text("VRAM Usage:");
				ImGui::SameLine();
				ImGui::TextColored(YELLOW_COLOR, "%f", float(hardware.VRAM_available) / (1024.f));

				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Input"))
			{
				ImGui::Spacing();

				ImGui::Text("Mouse Position:"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR, "%i, %i", App->input->GetMouseX(), App->input->GetMouseY());
				ImGui::Text("Mouse Motion:"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR, "%i,%i", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());
				ImGui::Text("Mouse Wheel:"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR, "%i", App->input->GetMouseZ());

				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Renderer"))
			{
				ImGui::Spacing();

				if (ImGui::TreeNodeEx("Background:", ImGuiTreeNodeFlags_None))
				{
					ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueBar;
					ImGui::Spacing();
					ImGui::Text("Color: "); ImGui::SameLine(); ImGui::PushItemWidth(180); ImGui::ColorEdit3(" ", (float*)&App->renderer3D->bg_color, flags);
					ImGui::TreePop();
				}

				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::TreeNodeEx("Grid:", ImGuiTreeNodeFlags_None)) 
				{
					ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueBar;
					ImGui::Spacing();
					ImGui::Text("Draw:  "); ImGui::SameLine(); ImGui::PushItemWidth(110); ImGui::PushID("drawG"); ImGui::Checkbox(" ", &App->scene_intro->drawGrid); ImGui::PopID();
					ImGui::Text("Size:  ");	ImGui::SameLine(); ImGui::PushItemWidth(130); ImGui::PushID("lenghtG"); ImGui::InputFloat(" ", &App->scene_intro->gridSize, 0.1f, 10.0f); ImGui::PopID();
					ImGui::Text("Width:  ");	ImGui::SameLine(); ImGui::PushItemWidth(130); ImGui::PushID("widthG"); ImGui::InputFloat(" ", &App->scene_intro->gridWidth, 1.0f, 10.0f); ImGui::PopID();
					ImGui::Text("Color: "); ImGui::SameLine(); ImGui::PushItemWidth(180); ImGui::ColorEdit3(" ", (float*)&App->scene_intro->gridColor, flags);
					ImGui::TreePop();
				}

				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::TreeNodeEx("Axis:", ImGuiTreeNodeFlags_None))
				{
					ImGui::Spacing();
					ImGui::Text("Length:  "); ImGui::SameLine(); ImGui::PushItemWidth(130); ImGui::PushID("lenghtG"); ImGui::InputFloat(" ", &App->scene_intro->axisLength, 0.1f, 10.0f); ImGui::PopID();
					ImGui::TreePop();
				}

				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::TreeNodeEx("Bounding Boxes:", ImGuiTreeNodeFlags_None))
				{
					ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueBar;
					ImGui::Spacing();
					ImGui::Text("Size: "); ImGui::SameLine(); ImGui::PushItemWidth(130); ImGui::PushID("Size"); ImGui::InputFloat(" ", &App->scene_intro->bbSize, 1.f, 10.0f); ImGui::PopID();
					ImGui::Text("Color: "); ImGui::SameLine(); ImGui::PushItemWidth(180); ImGui::ColorEdit3(" ", (float*)&App->scene_intro->bbColor, flags);
					ImGui::TreePop();
				}

				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::TreeNodeEx("Frustum:", ImGuiTreeNodeFlags_None))
				{
					ImGuiColorEditFlags flags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_PickerHueBar;
					ImGui::Spacing();
					ImGui::Text("Frustum: "); ImGui::SameLine(); ImGui::PushItemWidth(180); ImGui::ColorEdit3("##Frustum", (float*)&App->gui->frustum_color, flags);

					ImGui::Spacing();
					ImGui::Text("Planes: "); ImGui::SameLine(); ImGui::PushItemWidth(180); ImGui::ColorEdit3("##Planes", (float*)&App->gui->plane_color, flags);
					ImGui::TreePop();
				}

				ImGui::Separator();
				ImGui::Spacing();

				if (ImGui::TreeNodeEx("View Modes:", ImGuiTreeNodeFlags_DefaultOpen)) 
				{
					ImGui::Spacing(); 

					if (ImGui::Checkbox("Wireframe", &wireframe))
						App->renderer3D->WireframeView(wireframe);

					ImGui::SameLine();

					if (ImGui::Checkbox("Depth", &depth_test))
						App->renderer3D->DepthView(depth_test);
					
					ImGui::SameLine();

					if (ImGui::Checkbox("Cull Face", &cull_face))
						App->renderer3D->CullFaceView(cull_face);

					if (ImGui::Checkbox("Lighting", &lighting))
						App->renderer3D->LightingView(lighting);

					ImGui::SameLine();

					if (ImGui::Checkbox("Alpha", &alpha))
						App->renderer3D->AlphaView(alpha);

					ImGui::SameLine();

					if (ImGui::Checkbox("Texture 2D", &texture2D))
						App->renderer3D->Texture2DView(texture2D);

					ImGui::TreePop();
				}

				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Camera"))
			{
				ImGui::Spacing();

				if (ImGui::TreeNodeEx("Sensitivity", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Spacing();
					ImGui::PushItemWidth(150);
					ImGui::SliderFloat("Input Sensitivity", &App->camera->slow, 0.1f, 25.0f); 
					ImGui::SliderFloat("Camera Speed", &App->camera->currentSpeed, 0.1f, 100.0f);
					ImGui::SliderFloat("Wheel Zoom Speed", &App->camera->mouseWheelS, 0.1f, 100.0f);
					ImGui::SliderFloat("Focus Distance", &App->camera->distanceFocus, 0.1f, 50.0f);
					ImGui::TreePop();
				}

				ImGui::Spacing();
			}
		}

		ImGui::End();
	}

	return true;
}