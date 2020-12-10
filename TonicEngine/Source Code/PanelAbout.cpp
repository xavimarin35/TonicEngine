#include "PanelAbout.h"
#include "ModuleGUI.h"
#include "ModuleWindow.h"
#include "ModuleCamera3D.h"
#include "TextureImporter.h"
#include "ModuleResources.h"
#include "Resource.h"
#include "ResourceTexture.h"

PanelAbout::PanelAbout() : PanelManager()
{
}

PanelAbout::~PanelAbout()
{
}

bool PanelAbout::Start()
{
	this->active = false;
	
	icon = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/iconEngine.ico"));
	icon->LoadInMemory();

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
			ImGui::Image((ImTextureID*)icon->tex.id, ImVec2(35, 35), ImVec2(0, 1), ImVec2(1, 0)); ImGui::SameLine();
			
			ImGui::Text("%s by Pol Casau and Xavi Marin", SDL_GetWindowTitle(App->window->window));
			ImGui::Separator();

			ImGui::Text("This is a 3D Game Engine developed during our Game Design and Development Bachelor's Degree.");
			ImGui::Separator();

			if (ImGui::TreeNodeEx("Github Links", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth))
			{
				if (ImGui::Button("Repository"))
					App->RequestBrowser("https://github.com/xavimarin35/TonicEngine"); ImGui::SameLine();
				if (ImGui::Button("Pol Casau"))
					App->RequestBrowser("https://github.com/Bullseye14"); ImGui::SameLine();
				if (ImGui::Button("Xavi Marin"))
					App->RequestBrowser("https://github.com/xavimarin35");

				ImGui::TreePop();
			}
			
			ImGui::Separator();

			if (ImGui::TreeNodeEx("3rd Party Libraries", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth))
			{
				if (ImGui::Button("OpenGL"))
					App->RequestBrowser("https://www.opengl.org/"); ImGui::SameLine();
				if (ImGui::Button("Glew"))
					App->RequestBrowser("http://glew.sourceforge.net/"); ImGui::SameLine();
				if (ImGui::Button("SDL"))
					App->RequestBrowser("https://www.libsdl.org/"); ImGui::SameLine();
				if (ImGui::Button("ImGui"))
					App->RequestBrowser("https://github.com/ocornut/imgui"); ImGui::SameLine();
				if (ImGui::Button("PCG"))
					App->RequestBrowser("http://www.pcg-random.org/"); ImGui::SameLine();
				if (ImGui::Button("MathGeoLib"))
					App->RequestBrowser("https://github.com/juj/MathGeoLib"); ImGui::SameLine();
				if (ImGui::Button("Assimp"))
					App->RequestBrowser("https://www.assimp.org/"); ImGui::SameLine();
				if (ImGui::Button("DeviIL"))
					App->RequestBrowser("http://openil.sourceforge.net/"); ImGui::SameLine();
				if (ImGui::Button("PhysFS"))
					App->RequestBrowser("https://icculus.org/physfs/"); ImGui::SameLine();
				if (ImGui::Button("JSON"))
					App->RequestBrowser("https://github.com/nlohmann/json");

				ImGui::TreePop();
			}

			ImGui::Separator();

			ImGui::Text("MIT License");
			ImGui::Text("Copyright (c) 2020 Xavi Marin Sola and Pol Casau Civit");
			ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy of this");
			ImGui::Text("software and associated documentation files (the 'Software'), to deal in the Software without");
			ImGui::Text("restriction, including without limitation the rights to use, copy, modify, merge, publish,");
			ImGui::Text("distribute, sublicense, and / or sell copies of the Software, and to permit  persons");
			ImGui::Text("to whom the Software is furnished to do so, subject to the following conditions :");

			ImGui::Text("\nThe above copyright notice and this permission notice shall be included in all copies");
			ImGui::Text("or substantial portions of the Software.");

			ImGui::Text("\nTHE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,");
			ImGui::Text("INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A");
			ImGui::Text("PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS");
			ImGui::Text("BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,");
			ImGui::Text("TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE");
			ImGui::Text("USE OR OTHER DEALINGS IN THE SOFTWARE.");

			ImGui::End();
		}
	}

	return true;
}
