#include "ModuleTime.h"
#include "Application.h"
#include "Globals.h"


ModuleTime::ModuleTime(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleTime::~ModuleTime() {}


update_status ModuleTime::Update(float dt)
{
	if (!game_is_paused)
		time = real_time - started_timer - paused_time;
	else
		paused_time += real_dt;

	real_dt = App->GetDT();
	real_time += real_dt;

	return UPDATE_CONTINUE;
}

float ModuleTime::GetCurrentTimer() const
{
	return real_time;
}

float ModuleTime::GetPlayModeCurrentTime() const
{
	return time;
}

void ModuleTime::ResetGameTimer()
{
	time = 0.0f;
	paused_time = 0.0f;
	started_timer = 0.0f;
}


