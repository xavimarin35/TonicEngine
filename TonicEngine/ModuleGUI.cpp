#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"



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
	Phierarchy = new PanelHierarchy();
	Pconsole = new PanelConsole();
	Pinspector = new PanelInspector();
	
	PushBackPanels();

	return true;
}

bool ModuleGUI::Start()
{
	bool ret = true;


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io->DisplaySize.x = SCREEN_WIDTH;
	io->DisplaySize.y = SCREEN_HEIGHT;
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init(NULL);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->Start();
	}

	return ret;
}

update_status ModuleGUI::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

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

	bool opt_fullscreen = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	
	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	docking_io = &io;
	ImGui::End();

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

bool ModuleGUI::Draw()
{
	bool ret = true;

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
			ImGui::MenuItem("Console Window", NULL, &Pconsole->active);

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

	Render();

	return ret;
}

void ModuleGUI::EnableInput(SDL_Event* event)
{
	ImGui_ImplSDL2_ProcessEvent(event);
}

void ModuleGUI::PushBackPanels()
{
	panels.push_back(Pconfig);
	panels.push_back(Pabout);
	panels.push_back(Phierarchy);
	panels.push_back(Pconsole);
	panels.push_back(Pinspector);
}

void ModuleGUI::LogConsole(char* text, ...)
{
	char buf[1024];
	va_list args;
	va_start(args, text);
	vsnprintf(buf, IM_ARRAYSIZE(buf), text, args);
	buf[IM_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);
	App->appLogs.push_back(Strdup(buf));
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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	return ret;
}

void ModuleGUI::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glViewport(0,0,(int)docking_io->DisplaySize.x, (int)docking_io->DisplaySize.y);
	
}





