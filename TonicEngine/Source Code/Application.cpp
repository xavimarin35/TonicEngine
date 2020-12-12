#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleGui.h"
#include "PanelManager.h"
#include "MeshImporter.h"
#include "ModuleFileSystem.h"
#include "TextureImporter.h"
#include "JsonImporter.h"
#include "ModuleTime.h"
#include "ModuleResources.h"

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	gui = new ModuleGUI(this);
	mesh_imp = new MeshImporter(this);
	file_system = new ModuleFileSystem(this);
	tex_imp = new TextureImporter(this);
	time = new ModuleTime(this);
	resources = new ModuleResources(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);	
	AddModule(mesh_imp);
	AddModule(tex_imp);
	AddModule(file_system);
	AddModule(time);

	// Scenes
	AddModule(scene_intro);
	AddModule(gui);
	AddModule(resources);

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
	LOG_C("Init Application");

	// Locate .json path 
	jsonPath = "Configuration/config.json";
	// Load JSON data
	LoadJSON();

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
	
	frame_time.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = (float)frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	uint last_frame_ms = frame_time.Read();
	uint frames_on_last_update = prev_last_sec_frame_count;

	fpsVec.push_back(frames_on_last_update);
	if (fpsVec.size() > totalBars)
		fpsVec.erase(fpsVec.begin());

	msVec.push_back(last_frame_ms);
	if (msVec.size() > totalBars)
		msVec.erase(msVec.begin());

	if (framerateCap > 0)
		capped_ms = 1000 / framerateCap;
	else
		capped_ms = 0;

	if (capped_ms > 0 && last_frame_ms < capped_ms)
		SDL_Delay(capped_ms - last_frame_ms);
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

	if (quitApp)
		return UPDATE_STOP;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	SaveJSON();

	for (list<Module*>::reverse_iterator item = list_modules.rbegin(); item != list_modules.rend() && ret; ++item)
	{
		ret = (*item)->CleanUp();
	}

	return ret;
}

void Application::ChangeEngineState(ENGINE_STATE new_state)
{
	this->current_state = new_state;
}

bool Application::PlayScene()
{
	switch(current_state)
	{
	case ENGINE_STATE::NONE:
		if (camera->GetActiveCamera() != nullptr)
		{
			camera->activeCam = camera->playCam->GetComponentCamera();
			camera->activeCam->update_frustum = true;
			ChangeEngineState(ENGINE_STATE::PLAY);
			time->started_timer = time->GetCurrentTimer();
			LOG_C("PLAYMODE: Running");
			return true;
		}
		break;
	}

	return false;
}

void Application::PauseScene()
{
	switch (current_state)
	{
	case ENGINE_STATE::PLAY:
		ChangeEngineState(ENGINE_STATE::PAUSE);
		time->game_is_paused = true;
		LOG_C("PLAYMODE: Paused");
		break;
	
	case ENGINE_STATE::PAUSE:
		ChangeEngineState(ENGINE_STATE::PLAY);
		time->game_is_paused = false;
		LOG_C("PLAYMODE: Running");
		break;
	}
}

void Application::StopScene()
{
	switch (current_state) {
	case ENGINE_STATE::PLAY:
	case ENGINE_STATE::PAUSE:
		camera->activeCam = camera->mainCam;
		camera->mainCam->update_frustum = true;
		ChangeEngineState(ENGINE_STATE::NONE);
		time->game_is_paused = false;
		time->ResetGameTimer();
		LOG_C("PLAYMODE: Stopped");
		break;
	}
}

ENGINE_STATE Application::GetEngineState()
{
	return current_state;
}

void Application::RequestBrowser(const char* link) const
{
	LOG_C("WARNING: Browser Opened")
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

void Application::LoadJSON()
{
	json configData;

	assert(App->jsonPath != nullptr);

	std::ifstream stream;
	stream.open(App->jsonPath);

	std::list<Module*>::iterator it = App->list_modules.begin();

	configData = json::parse(stream);

	stream.close();

	std::string name = configData["Application"]["Name"];
	App->appName = name;

	// Load JSON data to all modules
	while (it != App->list_modules.end())
	{
		(*it)->Load(configData);
		it++;
	}
}

void Application::SaveJSON()
{
	json configData;

	configData["Application"]["Name"] = App->appName;

	std::list<Module*>::iterator it = App->list_modules.begin();

	// Save JSON data to all modules
	while (it != App->list_modules.end())
	{
		(*it)->Save(configData);
		it++;
	}

	std::ofstream stream;
	stream.open(App->jsonPath);
	stream << std::setw(4) << configData << std::endl;
	stream.close();
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

float Application::GetDT() const
{
	return dt;
}

std::string Application::GetPathName(std::string path)
{
	std::string string1 = path;
	uint num = string1.find_last_of("/\\");

	string1 = string1.substr(num + 1, string1.size());

	uint dot = string1.find_last_of(".");
	string1 = string1.substr(0, dot);

	return string1;
}

std::string Application::GetPathDir(std::string path)
{
	size_t found = path.find_last_of("/\\");

	std::string dir = path.substr(0, found);

	return dir;
}

int Application::GenerateUUID()
{
	int uuid = GenerateRandomBetween(99999999999);
	return uuid;
}

std::string Application::GetBuildingID(std::string path, std::string search)
{
	std::string newPath = path;

	if (search == "Plane") return "10";

	else
	{
		if (!isInCharStr(newPath.c_str(), search))
			return path;
		else
		{
			size_t i = 0;

			for (; i < newPath.length(); i++)
			{
				if (isdigit(newPath[i]))
					break;
			}

			newPath = newPath.substr(i, newPath.length() - i);

			uint _bar = newPath.find_last_of("_");
			newPath = newPath.substr(0, _bar);

			return newPath;
		}
	}
}

bool Application::isInCharStr(std::string path, std::string search)
{
	size_t found = path.find(search);

	if (found != string::npos) return true;

	else return false;
}