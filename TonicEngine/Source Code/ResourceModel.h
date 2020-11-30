#ifndef __ResourceModel_H__
#define __ResourceModel_H__

#include "Resource.h"

class ResourceModel : public Resource
{
public:

	ResourceModel(uint uuid) : Resource(uuid, RESOURCE_TYPE::MODEL) {}
	virtual ~ResourceModel() {}

	//void Save(const char* resourceNum, nlohmann::json &config) const;
	//void Load(const char* resourceNum, const nlohmann::json &config);

	bool LoadInMemory();
	void ReleaseMemory();

public:

};

#endif
