#ifndef __MODULETIME_H__
#define __MODULETIME_H__

#include "Module.h"
#include "Globals.h"


class ModuleTime : public Module
{
public:
	ModuleTime(Application* app, bool start_enabled = true);
	~ModuleTime();

	update_status Update(float dt);

	void ResetGameTimer();

	float GetCurrentTimer() const;
	float GetPlayModeCurrentTime() const;

	float paused_time = 0.0f;
	float started_timer = 0.0f;

	float time = 0.0f;
	float real_time = 0.0f;
	float real_dt = 0.0f;
	
	bool game_is_paused = false;
};

#endif 
