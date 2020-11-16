#ifndef __ModuleCamera3D__
#define __ModuleCamera3D__

#include "Module.h"
#include "glmath.h"
#include "GameObject.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();
	void GoInitialPos();

	bool isOnConsole = false;
	bool isOnHierarchy = false;
	bool isOnInspector = false;
	bool isOnConfiguration = false;
	bool isOnState = false;

	GameObject* cameraGO = nullptr;

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;
	float zoomValue = 0.5f; // Increases or decreases the sensitivity of zoom
	float wheelSpeedValue = 0.5f; // Increases or decreases the sensitivity of clicking wheel movement
	float WASDValue = 1.0f; // Increases or decreases the sensitivity of moving with WASD
	float distanceFocus = 8.0f; // Increases or decreases the distance from the game object when pressing F

	bool focusError = false;

private:

	mat4x4 ViewMatrix, ViewMatrixInverse;
};

#endif __ModuleCamera3D__