#include "PanelAbout.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"

#include "SDL/include/SDL_opengl.h"
#include "imgui-1.78/imgui_impl_sdl.h"

PanelAbout::PanelAbout() : PanelManager()
{
}

PanelAbout::~PanelAbout()
{
}

bool PanelAbout::Start()
{
	this->active = false;

	return true;
}

bool PanelAbout::Draw()
{
	if (!App->gui->Pabout->active)
		return false;

	if (App->gui->Pabout->active)
	{
		if (ImGui::Begin("About", &active, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::Text("%s ", SDL_GetWindowTitle(App->window->window));
			ImGui::Separator();

			ImGui::Text("3D Game Engine developed in C & C++ during our Game Design and Development Bachelor's Degree.");
			ImGui::Text("By Pol Casau and Xavi Marin\n");

			if (ImGui::Button("GitHub"))
				ShellExecuteA(NULL, "open", "https://github.com/xavimarin35/TonicEngine", NULL, NULL, SW_SHOWNORMAL);

			//ImGui::Separator();

			ImGui::Text("\n3rd Party Libraries used:");
			if (ImGui::Selectable("OpenGL", false, 0, { 50, 13 }))
				App->RequestBrowser("https://www.opengl.org/"); ImGui::SameLine();
			if (ImGui::Selectable("Glew", false, 0, { 35, 13 }))
				App->RequestBrowser("http://glew.sourceforge.net/"); ImGui::SameLine();
			if (ImGui::Selectable("SDL", false, 0, { 35, 13 }))
				App->RequestBrowser("https://www.libsdl.org/"); ImGui::SameLine();
			if (ImGui::Selectable("ImGui", false, 0, { 40, 13 }))
				App->RequestBrowser("https://github.com/ocornut/imgui"); ImGui::SameLine();
			if (ImGui::Selectable("PCG", false, 0, { 35, 13 }))
				App->RequestBrowser("http://www.pcg-random.org/"); ImGui::SameLine();
			if (ImGui::Selectable("MathGeoLib", false, 0, { 90, 13 }))
				App->RequestBrowser("https://github.com/juj/MathGeoLib");

			ImGui::Text("\nMIT License");
			ImGui::Text("Copyright (c) 2020 Xavi Marin Sola and Pol Casau Civit");
			ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
			ImGui::Text("of this software and associated documentation files (the 'Software'), to deal");
			ImGui::Text("in the Software without restriction, including without limitation the rights");
			ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and / or sell");
			ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
			ImGui::Text("furnished to do so, subject to the following conditions :");

			ImGui::Text("\nThe above copyright notice and this permission notice shall be included in all");
			ImGui::Text("copies or substantial portions of the Software.");

			ImGui::Text("\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
			ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
			ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
			ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
			ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
			ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
			ImGui::Text("SOFTWARE.");

			ImGui::End();
		}
	}
	return true;
}
