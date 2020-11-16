#ifndef __MODULETIME_H__
#define __MODULETIME_H__

#include "Module.h"
#include "Globals.h"


class ModuleTime : public Module
{
public:
	ModuleTime(Application* app, bool start_enabled = true);
	~ModuleTime();

	update_status PostUpdate(float dt);
	bool CleanUp();

	void ResetGameTimer();

	uint GetFrameCount() const;
	float GetRealTimeClock() const;
	float GetRealDT() const;
	float GetGameTime() const;
	float GetTimeScale() const;
	float GetGameDT() const;

public:

	float time_scale = 1.0f;

private:

	//Time in Engine, Real Time Clock
	uint frame_count = 0;
	float real_time = 0.0f;
	float real_dt = 0.0f;

	//Game clock
	float time = 0.0f;
	float dt = 0.0f;

};

#endif //!__TIME_MANAGER_H__
