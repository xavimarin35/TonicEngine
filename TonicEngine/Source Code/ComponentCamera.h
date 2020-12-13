#ifndef __C_CAMERA_H__
#define __C_CAMERA_H__

#include "Component.h"
#include "glmath.h"
#include "MathGeoLib/include/Geometry/Frustum.h"
#include "MathGeoLib/include/Geometry/LineSegment.h"
#include "MathGeoLib/include/Geometry/Plane.h"
#include "Color.h"

class GameObject;
class Plane;

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* GO = nullptr);
	~ComponentCamera();

	bool Start();
	bool Update();
	bool CleanUp();

	void DrawInspector();
	void DrawCamera();
	void LookAt(const float3& position);
	
	float4x4 GetViewMatrix() const;
	float4x4 GetProjectionMatrix() const;
	float4x4 GetView() const;
	float4x4 GetProjection() const;

	float GetFOV() const;
	float GetNearPlane() const;
	float GetFarPlane() const;
	float GetRatio() const;

	void SetNearPlane(float dist);
	void SetFarPlane(float dist);
	void SetFOV(float fov);
	void SetRatio(float ratio);

	void DrawFrustum();
	void AspectRatio(float ratio);

	Ray EyeRay(float x, float y) const;
	Ray NearRay(float x, float y) const;
	LineSegment NearSegment(float x, float y) const;

	bool Intersect(const AABB& box) const;
	static bool Intersect(const Frustum& frustum, const AABB& box);

	void Save(uint GO_id, nlohmann::json& scene_file);

public:

	Frustum frustum;
	bool showFrustum = false;
	bool seeFrustum = false;
	bool update_frustum = true;
};

#endif