#ifndef __ResourceTexture_H__
#define __ResourceTexture_H__

#include "Resource.h"
#include "TextureImporter.h"

struct Texture;

class ResourceTexture : public Resource
{
public:

	ResourceTexture(uint uuid) : Resource(uuid, RESOURCE_TYPE::TEXTURE) {}
	virtual ~ResourceTexture() {}

	//void Save(const char* resourceNum, nlohmann::json &config) const;
	//void Load(const char* resourceNum, const nlohmann::json &config);

	bool LoadInMemory();
	void ReleaseMemory();

public:

	Texture tex; // We will get texture id, width and height from here
	uint resource_texture = 0;

};

#endif
