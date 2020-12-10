#ifndef __ResourceScene_H__
#define __ResourceScene_H__

#include "Resource.h"

class ResourceScene : public Resource
{
public:

	ResourceScene(uint uuid) : Resource(uuid, RESOURCE_TYPE::SCENE) {}
	virtual ~ResourceScene() {}

	//void Save(const char* resourceNum, nlohmann::json &config) const;
	//void Load(const char* resourceNum, const nlohmann::json &config);

	bool LoadInMemory();
	void ReleaseMemory();

public:

};

#endif
