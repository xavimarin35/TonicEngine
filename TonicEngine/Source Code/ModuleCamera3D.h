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

	// Camera Movement
	void LookAt(const float3 &Spot, float dist = 0.0f);
	void Move(const float3 &Movement);
	void Focus(GameObject* GO);

	// Mouse Picking
	bool Intersects(const AABB& refBox) const;
	GameObject* MousePicking() const;

public:

	// Getters
	float3 GetPosition() const;
	float* GetView() const;
	float* GetProjection() const;
	bool* GetProjectionBool() const;
	ComponentCamera* GetActiveCamera();
	const Frustum& GetActiveFrustum() const;

private:

	// Other camera movements
	void MoveCamera(float& speed);
	void DragCamera(float x, float y);
	void Zoom(float z);

	void Orbit(float x, float y);
	void Rotate(float x, float y);
	void DrawRay();

	bool CheckMousePosition();

public:
	bool isOnConsole = false;
	bool isOnHierarchy = false;
	bool isOnInspector = false;
	bool isOnConfiguration = false;
	bool isOnState = false;
	bool isOnResources = false;
	bool isOnResourcesChild1 = false;
	bool isOnResourcesChild2 = false;
	bool isOnScene = false;
	bool isOnGame = false;
	bool isOnQuit = false;
	bool isOnSelectTexture = false;
	bool isOnMainBar = false;

	GameObject* cameraGO = nullptr;
	ComponentCamera* mainCam = nullptr;
	ComponentCamera* activeCam = nullptr;
	GameObject* playCam = nullptr;

	float3 looking_at;
	bool looking = false;
	bool mouse_picking = false;

public:
	
	float currentSpeed = 10.0f;
	float slow = 6.0f;
	float mouseWheelS = 30.0f;
	float distanceFocus = 15.0f; // Increases or decreases the distance from the game object when pressing F

	bool focusError = false;

private:

	LineSegment rayHit;
};

#endif __ModuleCamera3D__