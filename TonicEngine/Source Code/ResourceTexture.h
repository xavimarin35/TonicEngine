#ifndef __ResourceTexture_H__
#define __ResourceTexture_H__

#include "Resource.h"

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

};

#endif
