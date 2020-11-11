#ifndef __C_TEXTURE_H__
#define __C_TEXTURE_H__

#include "Component.h"
#include "glmath.h"
#include "TextureImporter.h"
#include "ModuleInput.h"

class GameObject;


class ComponentTexture : public Component
{
public:
	ComponentTexture(GameObject* gameObject);
	virtual ~ComponentTexture();

	void Draw();
	bool Update();

	void OpenTexturesMenu();

	void IsTextureComponentActive(GameObject* go);
	void GetTexturePath();

public:
	
	bool EnableCheckersTexture = false;
	bool EnableHouseTexture = true;
	bool noTexture = false;
	bool openMenuTex = false;

	Texture texture;
	Texture original_texture;

	int iterator = 0;
	uint selectTexture = 0;
};

#endif
