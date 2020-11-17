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

	float3 GetPosition() const;
	Quat GetQuatRotation() const;
	float3 GetEulerRotation() const;
	float3 GetScale() const;
	float4x4 GetTransform() const;
	float4x4 GetGlobalTransform() const;

	void SetPosition(float3& position);
	void SetRotation(float3& rotation);
	void SetScale(float3& scale);

	void SetGlobalTransform(float4x4 transform);
	void TransformGlobalMat(const float4x4& global);

	void UpdateTransform();
	void UpdateLocalTransform();
	
	void Reset(bool new_default = false);

	void Draw();

	void IsTransformComponentActive(GameObject* go);

public:
	float4x4 localMatrix = float4x4::identity;
	float4x4 globalMatrix = float4x4::identity;

	float3 position = float3::zero;
	Quat rotation_quaternion = Quat::identity;
	float3 rotation = float3::zero;
	float3 scale = float3::one;

	bool moved = false;
};

#endif
