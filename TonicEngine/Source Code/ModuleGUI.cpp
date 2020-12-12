#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"
#include "MeshImporter.h"
#include "ModuleFileSystem.h"
#include "ModuleCamera3D.h"
#include "imgui-1.78/ImGuizmo.h"


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
	Pstate = new PanelState();
	Presources = new PanelResources();
	Pscene = new PanelScene();
	Pgame = new PanelGame();
	Pcam = new PanelCameraPreview();
	
	PushBackPanels();

	ImGuizmo::Enable(true);

	return true;
}

bool ModuleGUI::Start()
{
	bool ret = true;


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;

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
	ImGuizmo::BeginFrame();

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->PreUpdate(dt);
	}

	return ret;
}

update_status ModuleGUI::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	ApplyDocking(windowDocking);

	return ret;
}

update_status ModuleGUI::PostUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->PostUpdate(dt);
	}

	if (App->scene_intro->GOselected != nullptr && App->scene_intro->GOselected->data.active)
		DrawGuizmo();

	if (ImGuizmo::IsUsing() == true)
		usingGizmo = true;
	else if (ImGuizmo::IsUsing() == false)
		usingGizmo = false;

	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && !usingGizmo && App->camera->mouse_picking)
	{
		GameObject* pick;

		pick = App->camera->MousePicking();

		if (pick != nullptr)
			App->scene_intro->GOselected = pick;
		else
			App->scene_intro->GOselected = nullptr;
	}

	return ret;
}

bool ModuleGUI::Draw()
{
	bool ret = true;

	GameObject* GO = App->scene_intro->GOselected;

	// Drawing all panels
	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->Draw();
	}

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::IsWindowHovered()) App->camera->isOnMainBar = true;
		else App->camera->isOnMainBar = false;

		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Save Scene", "CTRL+S", &saveSceneMenu);

			ImGui::MenuItem("Load Scene", "CTRL+A", &loadSceneMenu);

			ImGui::Separator();

			if (ImGui::MenuItem("Quit", "Alt+F4"))
				exitMenu = true;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("GameObject"))
		{
			if (ImGui::MenuItem("Create Empty GameObject"))
				App->scene_intro->CreateEmpty("Empty_", App->scene_intro->GOroot);

			if (ImGui::BeginMenu("Create GameObject"))
			{
				if (ImGui::MenuItem("Camera"))
					App->scene_intro->CreateCamera("New_Camera_", App->scene_intro->GOroot);

				ImGui::MenuItem("Light", NULL, false, false);

				ImGui::EndMenu();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Remove GameObjects"))
				App->scene_intro->RemoveAllGO();

			ImGui::Separator();

			if (ImGui::BeginMenu("Create Basic Shape"))
			{
				if (ImGui::MenuItem("Cube"))
					App->scene_intro->Create3DObject(OBJECTS3D::B_CUBE);

				if (ImGui::MenuItem("Sphere"))
					App->scene_intro->Create3DObject(OBJECTS3D::B_SPHERE);

				if (ImGui::MenuItem("Cone"))
					App->scene_intro->Create3DObject(OBJECTS3D::B_CONE);

				if (ImGui::MenuItem("Cylinder"))
					App->scene_intro->Create3DObject(OBJECTS3D::B_CYLINDER);

				ImGui::Separator();

				if (ImGui::MenuItem("Baker House"))
					App->scene_intro->Create3DObject(OBJECTS3D::BAKER_HOUSE);

				if (ImGui::MenuItem("Street"))
				{
					App->scene_intro->Create3DObject(OBJECTS3D::STREET);
					LOG_C("WARNING: This model is has many polys. Loading it can take a while.")
				}
					
				ImGui::EndMenu();
			}

			HelpMarker("Game assets from The Witcher: Ties of Destiny");
			ImGui::SameLine();

			if (ImGui::BeginMenu("Create Other"))
			{

				if (ImGui::MenuItem("Geralt of Rivia"))
				{
					App->scene_intro->Create3DObject(OBJECTS3D::GERALT);
					LOG_C("WARNING: This 3D model has so many polys. The performance of the engine could be affected");
				}

				if (ImGui::MenuItem("Light post"))
					App->scene_intro->Create3DObject(OBJECTS3D::LIGHTPOST);

				if (ImGui::MenuItem("Carriage"))
					App->scene_intro->Create3DObject(OBJECTS3D::CARRIAGE);

				if (ImGui::MenuItem("Rock"))
					App->scene_intro->Create3DObject(OBJECTS3D::ROCK);

				ImGui::Separator();

				if (ImGui::MenuItem("Visit Ties of Destiny!"))
					App->RequestBrowser("https://tiesofdestiny.com/index.html");

				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Debug"))
		{
			if (ImGui::MenuItem("Create Empty x5"))
			{
				for (int i = 0; i < 5; i++)
				{
					GameObject* go = App->scene_intro->CreateGO("Empty");
					App->scene_intro->GOroot->AddChild(go);
				}
			}

			if (GO == nullptr)
			{
				HelpMarker("You must select a GO to use this tool");
				ImGui::SameLine();
			}

			if (ImGui::MenuItem("Delete Selected GO"))
			{
				App->scene_intro->RemoveSelectedGO(GO);
			}

			ImGui::Separator();

			if (GO == nullptr)
			{
				HelpMarker("You must select a GO to use this tool");
				ImGui::SameLine();
			}

			if (ImGui::BeginMenu("Get GO Information"))
			{
				if (GO != nullptr)
				{
					if (ImGui::MenuItem("Name"))
					{
						const char* name = App->scene_intro->GOselected->GetGameObjectName();
						LOG_C("The Name of the selected GO is: %s", name);
					}

					if (ImGui::MenuItem("ID"))
					{
						uint id = App->scene_intro->GOselected->GetGameObjectId();
						LOG_C("The ID of the selected GO is: %i", id);
					}

					if (ImGui::MenuItem("UUID"))
					{
						int uuid = App->scene_intro->GOselected->GetGameObjectUUID();
						LOG_C("The UUID of the selected GO is: %i", uuid);
					}
				}

				ImGui::EndMenu();
			}

			// --------------------------
			if (GO == nullptr)
			{
				HelpMarker("You must select a GO to use this tool");
				ImGui::SameLine();
			}

			if (ImGui::BeginMenu("Is Component Active"))
			{
				if (GO != nullptr)
				{
					if (ImGui::MenuItem("Transform"))
						GO->GetComponentTransform()->IsTransformComponentActive(GO);

					if (ImGui::MenuItem("Mesh"))
						GO->GetComponentMesh()->IsMeshComponentActive(GO);

					if (ImGui::MenuItem("Texture"))
						GO->GetComponentTexture()->IsTextureComponentActive(GO);
				}

				ImGui::EndMenu();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Number of GameObjects"))
				App->scene_intro->NumberOfGO();

			if (GO == nullptr)
			{
				HelpMarker("You must select a GO to use this tool");
				ImGui::SameLine();
			}

			if (ImGui::MenuItem("Get active GO index"))
			{
				if (GO != nullptr)
					App->scene_intro->GetGameObjectSelectedIndex(GO);
				else
					LOG_C("WARNING: You must select a GO to get the index");
			}
				
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			ImGui::MenuItem("Configuration Window", NULL, &Pconfig->active);
			ImGui::MenuItem("Demo Window", NULL, &show_demo_window);
			ImGui::MenuItem("Style Editor Window", NULL, &show_style_editor);
			ImGui::MenuItem("Hierarchy Window", NULL, &Phierarchy->active);
			ImGui::MenuItem("Console Window", NULL, &Pconsole->active);
			ImGui::MenuItem("Inspector Window", NULL, &Pinspector->active);
			ImGui::MenuItem("Engine State Window", NULL, &Pstate->active);
			ImGui::MenuItem("Resources Window", NULL, &Presources->active);
			ImGui::MenuItem("Scene Window", NULL, &Pscene->active, false);
			ImGui::MenuItem("Game Window", NULL, &Pgame->active, false);
			ImGui::MenuItem("Camera Preview Window", NULL, &Pcam->active, false);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("About Tonic Engine", NULL, &Pabout->active);

			ImGui::Separator();

			if (ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://github.com/xavimarin35/TonicEngine/blob/master/README.md");

			if (ImGui::MenuItem("Download Latest Version"))
				App->RequestBrowser("https://github.com/xavimarin35/TonicEngine/releases");

			ImGui::Separator();

			if (ImGui::MenuItem("Report Bug"))
				App->RequestBrowser("https://github.com/xavimarin35/TonicEngine/issues");

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();

	}

	if (saveSceneMenu)
	{
		ImGui::OpenPopup("Save Scene");
		if (ImGui::BeginPopupModal("Save Scene", &saveSceneMenu, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{

			ImGui::Spacing();
			
			// Saving scene name with a new index every time
			for (int i = 0; i < App->scene_intro->maxScenes; i++)
			{
				int aux = i;
				i = App->scene_intro->numScene;
				break;
			}

			string name = "Scene_";
			string finalName = name.append(std::to_string(App->scene_intro->numScene));

			ImGui::InputText("", (char*)finalName.c_str(), 35);
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				App->scene_intro->SaveScene(finalName);
				App->scene_intro->numScene++;
				saveSceneMenu = false;
			}

			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				saveSceneMenu = false;
			}

			ImGui::Spacing();

			ImGui::Text("The scene will be stored in"); ImGui::SameLine(); ImGui::TextColored(YELLOW_COLOR,"Assets/Scenes/%s.json", finalName.c_str());
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::TextColored(GREY_COLOR,"Tonic Engine/Game/Assets/Scenes/%s.json", finalName.c_str());
				ImGui::EndTooltip();
			}

			ImGui::EndPopup();
		}
	}

	if (loadSceneMenu)
	{
		ImGui::OpenPopup("Load Scene");
		if (ImGui::BeginPopupModal("Load Scene", &loadSceneMenu, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{
			ImGui::Spacing();
			
			// Search in the specified folder and show the current files
			vector<string> file_list, dir_list;
			App->file_system->DiscoverFiles("Assets/Scenes/", file_list, dir_list);

			// Create buttons with the files saved
			for (vector<string>::iterator iterator = file_list.begin(); iterator != file_list.end(); iterator++)
			{
				if (ImGui::Button((*iterator).c_str(), ImVec2(300, 20)))
				{
					App->scene_intro->LoadScene((*iterator).c_str());
					loadSceneMenu = false;
				}
			}

			if (ImGui::Button("Cancel"))
			{
				loadSceneMenu = false;
			}
			ImGui::EndPopup();
		}
	}

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	if (show_style_editor)
	{
		ImGui::Begin("Style Editor Window", &show_style_editor);
		ImGui::ShowStyleEditor();
		ImGui::End();
	}

	if (exitMenu)
	{
		App->camera->isOnQuit = true;

		ImGui::OpenPopup("Quit");
		if (ImGui::BeginPopupModal("Quit", &exitMenu, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse))
		{

			ImGui::Text("Exit from Tonic Engine?");
			ImGui::Spacing();

			if (ImGui::Button("Yes", ImVec2(77.0f, 25.0f)))
				App->quitApp = true;

			ImGui::SameLine();

			if (ImGui::Button("No", ImVec2(77.0f, 25.0f)))
			{
				App->quitApp = false;
				exitMenu = false;
			}	

			ImGui::Spacing();
			ImGui::EndPopup();
		}
	}
	else
	{
		App->camera->isOnQuit = false;
	}

	if (deleteScene)
		App->scene_intro->DeleteScene();

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
	panels.push_back(Pstate);
	panels.push_back(Presources);
	panels.push_back(Pscene);
	panels.push_back(Pgame);
	panels.push_back(Pcam);
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
}

void ModuleGUI::ChangeOperationGuizmo(ImGuizmo::OPERATION& op)
{
	if (currentOp == 1) {
		op = ImGuizmo::OPERATION::TRANSLATE;
	}
	if (currentOp == 2) {
		op = ImGuizmo::OPERATION::ROTATE;
	}
	if (currentOp == 3) {
		op = ImGuizmo::OPERATION::SCALE;
	}
}

void ModuleGUI::DrawGuizmo()
{
	if (App->scene_intro->GOselected == nullptr) return;

	GameObject* GO = App->scene_intro->GOselected;
	ComponentTransform* transf = (ComponentTransform*)GO->GetComponent(COMPONENT_TYPE::TRANSFORM);

	// View parametres
	float4x4 view_matrix = App->camera->GetActiveCamera()->frustum.ViewMatrix();
	view_matrix.Transpose();
	float4x4 proj_matrix = App->camera->GetActiveCamera()->frustum.ProjectionMatrix().Transposed();

	// Draw guizmos axis
	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	// Change guizmos operations
	ChangeOperationGuizmo(g_operator);

	float4x4 matrix;
	matrix = transf->globalMatrix.Transposed();

	ImGuizmo::MODE actualMode = (g_operator == ImGuizmo::OPERATION::SCALE ? ImGuizmo::MODE::LOCAL : mode);

	ImGuizmo::Manipulate(view_matrix.ptr(), proj_matrix.ptr(), g_operator, actualMode, (float*)matrix.v);

	if (ImGuizmo::IsUsing() == true)
	{
		float4x4 newMatrix;
		newMatrix.Set(matrix);

		newMatrix.Transpose();

		if (CheckParent(GO->GOparent))
		{
			transf->globalMatrix = newMatrix;
		}
		else
			transf->UpdateGizmo(newMatrix);
	}
}

void ModuleGUI::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void ModuleGUI::ApplyDocking(bool* window)
{
	bool opt_fullscreen = true;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	

	dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	ImGui::PopStyleVar();

	ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();
}

bool ModuleGUI::CheckParent(GameObject* GO)
{
	if (GO->data.name == "Dummy001" || GO->data.name == "City_building_010" || GO->data.name == "City_building_016" || GO->data.name == "City_building_017" || GO->data.name == "Street_V04")
		return true;

	else return false;
}