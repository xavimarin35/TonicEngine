#ifndef __C_TRANSFORM_H__
#define __C_TRANSFORM_H__

#include "Component.h"
#include "glmath.h"

#include "MathGeoLib/include/MathBuildConfig.h"
#include "MathGeoLib/include/MathGeoLib.h"

class GameObject;

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* gameObject);
	virtual ~ComponentTransform();

	// Getters
	float3 GetPosition() const;
	Quat GetQuatRotation() const;
	float3 GetEulerRotation() const;
	float3 GetScale() const;
	float4x4 GetTransform() const;
	float4x4 GetGlobalTransform() const;

	// Setters
	void SetPosition(float3& position);
	void SetEulerRotation(float3 rotation);
	void SetScale(float3& scale);
	void SetGlobalTransform(float4x4 transform);

	void TransformGlobalMat(const float4x4& global);

	// Updates
	void UpdateTransform();
	void UpdateLocalTransform();
	void UpdateGizmo(float4x4 newMatrix);
	
	// Reset
	void Reset(bool new_default = false);
	void SetNewDefault(float3 pos, float3 rot, float3 sc);
	void ResetTransform();

	void DrawInspector();

	void IsTransformComponentActive(GameObject* go);

	void Save(uint GO_id, nlohmann::json& scene_file);

public:
	float4x4 localMatrix = float4x4::identity;
	float4x4 globalMatrix = float4x4::identity;

	float3 default_position = float3::zero;
	Quat default_rotation_q = Quat::identity;
	float3 default_rotation_e = float3::zero;
	float3 default_scale = float3::one;

	float3 position = float3::zero;
	Quat rotation_quaternion = Quat::identity;
	float3 rotation_euler = float3::zero;
	float3 scale = float3::one;

	bool moved = false;

private:

	bool new_default = false;
};

#endif
