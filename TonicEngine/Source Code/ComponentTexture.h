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

	void OpenTexturesMenu();

	void IsTextureComponentActive(GameObject* go);
	void GetTexturePath();

	void Save(uint obj_num, nlohmann::json& scene_file);

public:
	
	bool EnableCheckersTexture = false;
	bool EnableAssignedTexture = true;
	bool noTexture = false;
	bool openMenuTex = false;

	Texture texture;
	Texture original_texture;

	int iterator = 0;
	uint selectTexture = 0;

	ResourceTexture* rTexture = nullptr;
};

#endif
