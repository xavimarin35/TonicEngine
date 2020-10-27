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

public:
	
	bool EnableCheckersTexture;
	bool EnableHouseTexture;

	texData tData;
};

#endif
