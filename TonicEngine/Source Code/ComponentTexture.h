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
	//bool openMenuTex2 = false;
	
	string texture_path;
	uint texture_width = 0;
	uint texture_height = 0;

	uint texture = 0;
	uint original_texture = 0;

	int iterator = 0;
	uint selectTexture = 0;
};

#endif
