#ifndef __Resource_H__
#define __Resource_H__

#include "Globals.h"
#include "Application.h"

enum class RESOURCE_TYPE
{
	NONE = -1,
	MESH,
	TEXTURE,
	MODEL
};

class Resource
{

public:
	Resource(uint UUID, RESOURCE_TYPE type) : res_UUID(UUID), type(type) {}
	virtual ~Resource() {}

	virtual bool LoadInMemory() = 0;
	virtual void ReleaseMemory() = 0;

	RESOURCE_TYPE GetType() const;
	uint GetUUID() const;
	uint GetCurrentReference();

public:
	RESOURCE_TYPE type = RESOURCE_TYPE::NONE;

	uint res_UUID = 0;
	std::string file = "";
	std::string exported_file = "";
	uint loaded = 0;
	uint references = 0;
};

#endif