#ifndef __C_CAMERA_H__
#define __C_CAMERA_H__

#include "Component.h"
#include "glmath.h"

class GameObject;

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* GO = nullptr);
	~ComponentCamera();

	bool Start();
	bool Update();
	bool CleanUp();
	void Draw();
	void LookAt(const float3& position);

	float GetFOV() const;
	float GetNearPlane() const;
	float GetFarPlane() const;

	void DrawFrustum();

private:

	math::Frustum frustum;
	bool showFrustrum = true;

public:

	vec3 X, Y, Z, Position, Reference;

};

#endif