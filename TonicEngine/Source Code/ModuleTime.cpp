#include "ModuleTime.h"
#include "Application.h"
#include "Globals.h"


ModuleTime::ModuleTime(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleTime::~ModuleTime() {}


update_status ModuleTime::PostUpdate(float dt)
{
	frame_count++;

	real_dt = App->GetDT();
	real_time += real_dt;

	return UPDATE_CONTINUE;
}

bool ModuleTime::CleanUp()
{
	return true;
}

void ModuleTime::ResetGameTimer()
{
	time = 0.0f;
	dt = 0.0f;
}

uint ModuleTime::GetFrameCount() const
{
	return frame_count;
}

float ModuleTime::GetRealTimeClock() const
{
	return real_time;
}

float ModuleTime::GetRealDT() const
{
	return real_dt;
}

float ModuleTime::GetGameTime() const
{
	return time;
}

float ModuleTime::GetTimeScale() const
{
	return time_scale;
}

float ModuleTime::GetGameDT() const
{
	return dt;
}