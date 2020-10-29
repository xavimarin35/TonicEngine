#ifndef __C_TRANSFORM_H__
#define __C_TRANSFORM_H__

#include "Component.h"
#include "glmath.h"

class GameObject;

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* gameObject, bool active);
	virtual ~ComponentTransform();

	void Draw();

	void IsTransformComponentActive(GameObject* go);

public:
	vec3 position;
	vec3 rotation;
	vec3 scale;
};

#endif
