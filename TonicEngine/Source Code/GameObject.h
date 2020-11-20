#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Application.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentTexture.h"
#include "ComponentCamera.h"
#include "ModuleInput.h"
#include "imgui-1.78/ImGuizmo.h"

class ComponentTransform;
class ComponentMesh;
class ComponentTexture;
class ComponentCamera;

struct goData;
struct meshData;

struct goData {
	uint id = -1;
	int UUID = 0;
	string name;
	bool active = true;
};

class GameObject
{
public:
	GameObject(std::string name);
	virtual ~GameObject();

	void Update();
	void CleanUp();
	//void Draw();

	void EnableGameObject();
	void DisableGameObject();

	bool IsGameObjectActive();
	const char* GetGameObjectName();
	uint GetGameObjectId();
	int GetGameObjectUUID();

	Component* CreateComponent(COMPONENT_TYPE type, bool active = true);
	Component* GetComponent(const COMPONENT_TYPE& type);

	ComponentTransform* GetComponentTransform();
	ComponentMesh* GetComponentMesh();
	ComponentTexture* GetComponentTexture();
	ComponentCamera* GetComponentCamera();

	GameObject* GetRootGameObject();
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);

	void TransformGlobal(GameObject* GO);

	int GenerateUUID();

	void UpdateBoundingBox();
	void DrawAllBoundingBoxes();
	void DrawOwnBoundingBox(GameObject* GO);

	//void RayCast(const LineSegment& ray_cast, bool& intersect, float& length);

	//void Load(const nlohmann::json& scene_file);
	void Save(uint obj_num, nlohmann::json& scene_file);

public:
	goData data;

	std::vector<Component*> componentsList;

	std::vector<GameObject*> childrenList;
	GameObject* GOparent = nullptr;

	AABB aabb;
	OBB obb;

};

#endif
