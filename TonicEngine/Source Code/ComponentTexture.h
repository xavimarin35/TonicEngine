#ifndef __C_TEXTURE_H__
#define __C_TEXTURE_H__

#include "Component.h"
#include "TextureImporter.h"
#include "ResourceTexture.h"

class GameObject;

class ComponentTexture : public Component
{
public:
	ComponentTexture(GameObject* gameObject);
	virtual ~ComponentTexture();

	void DrawInspector();
	bool Update();
	bool CleanUp();

	void OpenTexturesMenu();

	void IsTextureComponentActive(GameObject* go);
	void GetTexturePath();

	void Save(uint GO_id, nlohmann::json& scene_file);

public:
	
	bool EnableCheckersTexture = false;
	bool EnableAssignedTexture = true;
	bool noTexture = false;
	bool openMenuTex = false;

	Texture texture;

	ResourceTexture* rTexture = nullptr;
};

#endif
