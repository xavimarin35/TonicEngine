#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Application.h"

class GameObject;

enum class COMPONENT_TYPE
{
	NONE = -1,
	TRANSFORM,
	MESH,
	TEXTURE, 
	CAMERA
};

class Component
{
public:
	Component(COMPONENT_TYPE type, GameObject* GO = nullptr, bool active = true);
	virtual ~Component();

	virtual bool Update();
	virtual bool CleanUp();

	virtual void Draw();
	virtual void DrawInspector();
	COMPONENT_TYPE GetComponentType() const;
	virtual void EnableComponent();
	virtual void DisableComponent();

	virtual void Load(uint GO_id, const nlohmann::json& scene_file) {}
	virtual void Save(uint GO_id, nlohmann::json& scene_file) {}

public:
	bool active = false;
	COMPONENT_TYPE type = COMPONENT_TYPE::NONE;
	GameObject* object = nullptr;
	uint UUID = 0;
};

#endif