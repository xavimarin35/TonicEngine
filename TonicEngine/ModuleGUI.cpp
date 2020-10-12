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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io; ---> It doesn't work, must check it out
	io = &ImGui::GetIO(); (void)io;

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();

	// Panels
	Pconfig = new PanelConfiguration();
	panels.push_back(Pconfig);

	return true;

}

bool ModuleGUI::Start()
{
	bool ret = true;

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

	MainMenuBar();

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->Draw();
	}

	Render();

	return ret;
}

update_status ModuleGUI::MainMenuBar()
{
	update_status ret = UPDATE_CONTINUE;

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Config Panel", NULL, &configPanel_visible);
			ImGui::EndMenu();

		}
		ImGui::EndMainMenuBar();
	}

	return ret;
}

update_status ModuleGUI::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	for (list<PanelManager*>::const_iterator it = panels.begin(); it != panels.end(); ++it)
	{
		ret = (*it)->PreUpdate(dt);
	}

	return ret;
}

//update_status ModuleGUI::Update(float dt)
//{
	//update_status ret = UPDATE_CONTINUE;

	//ImVec4 clear_color = ImVec4(0.15f, 0.15f, 0.15f, 0.50f);
	//// Poll and handle events (inputs, window resize, etc.)
	//	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	//	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
	//	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
	//	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	//SDL_Event event;
	//while (SDL_PollEvent(&event))
	//{
	//	ImGui_ImplSDL2_ProcessEvent(&event);
	//}
	//
	////glfwPollEvents(); ---> Wasn't able to use this function
	//

	//// Start the Dear ImGui frame
	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplSDL2_NewFrame(App->window->window);
	//ImGui::NewFrame();

	//// My Main Menu
	//if (ImGui::BeginMainMenuBar())
	//{
	//	if (ImGui::BeginMenu("File"))
	//	{
	//		if (ImGui::MenuItem("Demo Window"))
	//			show_demo_window = !show_demo_window;

	//		if (ImGui::MenuItem("Custom Window"))
	//			show_custom_window = !show_custom_window;

	//		if (ImGui::MenuItem("Quit"))
	//			ret = UPDATE_STOP;
	//		ImGui::EndMenu();

	//	}
	//	ImGui::EndMainMenuBar();
	//}

	//// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	//// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	//
	//if (show_custom_window) 
	//{
	//	static float f = 0.0f;
	//	static int counter = 0;

	//	ImGui::Begin("Custom Window");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::Text("Welcome to 3D TonicEngine");               // Display some text (you can use a format strings too)
	//	//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
	//	ImGui::Checkbox("Another Window", &show_another_window);

	//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//		counter++;
	//	ImGui::SameLine();
	//	ImGui::Text("counter = %d", counter);

	//	// Random Number Generator
	//	if (ImGui::Button("Random"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
	//		rand = GenerateRandomBetween(100);
	//	ImGui::SameLine();
	//	ImGui::Text("%d", rand);


	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	ImGui::End();
	//}

	//// 3. Show another simple window.
	//if (show_another_window)
	//{
	//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable and creates a close button (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me"))
	//		show_another_window = false;
	//	ImGui::End();
	//}

	//// My Quit button 
	///*ImGui::SetNextWindowPos(ImVec2(0, 20));
	//ImGui::SetNextWindowSize(ImVec2(110, 60));
	//ImGui::Begin(" ", &show_close_app_window);   // Pass a pointer to our bool variable
	//if (ImGui::Button("Close Engine"))
	//	return UPDATE_STOP;
	//ImGui::End();*/


	//ImGuiIO& test_io = *io; 

	//// Calling ImGui Render functions
	//Render();

	//glViewport(0, 0, (int)test_io.DisplaySize.x, (int)test_io.DisplaySize.y);
	//glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//

	//// If these lines are not commented, the engine gifts you with an epileptic attack
	///*glClear(GL_COLOR_BUFFER_BIT);
	//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound*/
	////SDL_GL_SwapWindow(App->window->window); ---> THIS IS DONE IN THE RENDERER3D MODULE

//	return ret;
//}

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
	}

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


