#include "ModuleGUI.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"


ModuleGUI::ModuleGUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleGUI::~ModuleGUI()
{
}

bool ModuleGUI::Init()
{

	return true;
}


bool ModuleGUI::Start()
{

	return true;
}

update_status ModuleGUI::Update(float dt)
{


	return UPDATE_CONTINUE;
}