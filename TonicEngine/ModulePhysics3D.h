#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"


struct PhysBody3D;
struct PhysVehicle3D;

class ModulePhysics3D : public Module
{
public:
	ModulePhysics3D(Application* app, bool start_enabled = true);
	~ModulePhysics3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

};
