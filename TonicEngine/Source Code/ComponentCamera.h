#ifndef __C_CAMERA_H__
#define __C_CAMERA_H__

#include "Component.h"
#include "glmath.h"

class GameObject;

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* GO);
	~ComponentCamera();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3& Position, const vec3& Reference, bool RotateAroundReference = false);
	void LookAt(const vec3& Spot);
	void Move(const vec3& Movement);
	float* GetViewMatrix();
	void GoInitialPos();

	bool isOnConsole = false;
	bool isOnHierarchy = false;
	bool isOnInspector = false;
	bool isOnConfiguration = false;

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

#endif