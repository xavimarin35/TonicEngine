#ifndef __C_TEXTURE_H__
#define __C_TEXTURE_H__

#include "Component.h"
#include "glmath.h"
#include "TextureImporter.h"

class GameObject;


class ComponentTexture : public Component
{
public:
	ComponentTexture(GameObject* gameObject, bool active);
	virtual ~ComponentTexture();

	void Draw();
	bool Update();

	void OpenTexturesMenu();
	void OpenTexturesMenu2();

	void IsTextureComponentActive(GameObject* go);

public:
	
	bool EnableCheckersTexture = false;
	bool EnableHouseTexture = true;
	bool noTexture = false;
	bool openMenuTex = false;
	bool openMenuTex2 = false;

	texData tData;
	
	string texture_path;
	uint texture = 0;
	uint original_texture = 0;
};

#endif
