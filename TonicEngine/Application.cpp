#include "Application.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	gui = new ModuleGUI(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);	
	
	// Scenes
	AddModule(scene_intro);
	AddModule(gui);
	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	list<Module*>::iterator item = list_modules.begin();

	for (; item != list_modules.end(); item = next(item))
	{
		RELEASE(*item);
	}

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Needed to initialize PCG (Random Number Generator Library)
	InitSeed();

	// Call Init() in all modules
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret; ++item)
	{
		ret = (*item)->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret; ++item)
	{
		ret = (*item)->Start();
	}
	
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;

	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	last_fps = 1.0f / dt;
	last_ms = (float)ms_timer.Read();
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; ++item) 
	{
		ret = (*item)->PreUpdate(dt);
	}

	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; ++item)
	{
		ret = (*item)->Update(dt);
	}
	
	for (list<Module*>::iterator item = list_modules.begin(); item != list_modules.end() && ret == UPDATE_CONTINUE; ++item)
	{
		ret = (*item)->PostUpdate(dt);
		
	}
	
	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.rend() && ret; ++item)
	{
		ret = (*item)->CleanUp();
	}

	return ret;
}

void Application::RequestBrowser(const char* link) const
{
	ShellExecuteA(NULL, "open", link, NULL, NULL, SW_SHOWNORMAL);
}

const char* Application::GetAppName() const
{
	return appName.data();
}

const char* Application::GetOrgName() const
{
	return orgName.data();
}

void Application::ApplyAppName(const char* name)
{
	appName.assign(name);
	App->window->SetTitle(appName.data());
}

void Application::ApplyOrgName(const char* name)
{
	orgName = name;
}

float Application::GetMS()
{
	return last_ms;
}

float Application::GetFPS()
{
	return last_fps;
}

int Application::getFrameRateCap()
{
	return framerateCap;
}

void Application::setFrameRateCap(int cap)
{
	framerateCap = cap;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

float Application::GetDT() const
{
	return dt;
}


