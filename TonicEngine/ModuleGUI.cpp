#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "imgui-1.78/imgui_impl_opengl2.h"
//#include "imgui-1.78/examples/libs/glfw/include/GLFW/glfw3.h"

#pragma comment (lib, "imgui-1.78/examples/libs/glfw/lib-vc2010-32/glfw3.lib")


ModuleGUI::ModuleGUI(Application * app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleGUI::~ModuleGUI()
{
}

bool ModuleGUI::Init()
{
	// Panels
	Pconfig = new PanelConfiguration();
	Pabout = new PanelAbout();
	Pconsole = new PanelConsole();
	Phierarchy = new PanelHierarchy();

	panels.push_back(Pconfig);
	panels.push_back(Pabout);
	panels.push_back(Pconsole);
	panels.push_back(Phierarchy);

	return true;
}

bool ModuleGUI::Start()
{
	bool ret = true;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->Start();
	}

	return ret;
}

bool ModuleGUI::Draw()
{
	bool ret = true;

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->Draw();
	}

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Quit"))
				quitApp = true;

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::MenuItem("Configuration Window", NULL, &Pconfig->active);
			ImGui::MenuItem("Demo Window", NULL, &show_demo_window);
            ImGui::MenuItem("Style Editor Window", NULL, &show_style_editor);
			ImGui::MenuItem("Hierarchy Window", NULL, &Phierarchy->active);
				
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("About Panel", NULL, &Pabout->active);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
        
	}

	// Demo Window
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	
    if (show_style_editor)
    {
        ImGui::Begin("Style Editor Window", &show_style_editor);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }
        
		
    ImGuiIO& test_io = *io; // I think is used for docking
	Render();

	return ret;
}

update_status ModuleGUI::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	//SDL_Event event;
	//while (SDL_PollEvent(&event))
	//{
	//	ImGui_ImplSDL2_ProcessEvent(&event);
	//}

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->PreUpdate(dt);
	}

	return ret;
}

update_status ModuleGUI::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	if (quitApp)
		ret = UPDATE_STOP;

	return ret;
}

update_status ModuleGUI::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it) 
	{
		ret = (*it)->PostUpdate(dt);
	}

	return ret;
}

bool ModuleGUI::CleanUp()
{
	bool ret = true;

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->CleanUp();
		delete (*it);
	}

	panels.clear();

	ImGui_ImplSDL2_Shutdown();
	ImGui_ImplOpenGL2_Shutdown();
	ImGui::DestroyContext();

	return ret;
}

void ModuleGUI::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}





