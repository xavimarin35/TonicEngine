#ifndef __Resource_H__
#define __Resource_H__

#include "Globals.h"
#include "Application.h"

class Resource
{

public:
	enum RESOURCE_TYPE {
		TEXTURE,
		MESH,
		SCENE,
		UNKNOWN
	};

	Resource(uint UUID, RESOURCE_TYPE type) : res_UUID(UUID), type(type) {}
	virtual ~Resource() {}
	RESOURCE_TYPE GetType() const;

	bool IsLoadedToMemory() const;
	bool LoadToMemory();
	uint CountReferences() const;

	// Getters ----
	uint GetUUID() const { return res_UUID; }
	const char* GetFile() const;
	const char* GetImportedFile() const;


	virtual void Load(const nlohmann::json& config);
	virtual void Save(nlohmann::json& config) const;
	virtual bool LoadInMemory() = 0;

protected:
	uint res_UUID = 0;
	std::string file;
	std::string imported_file;
	RESOURCE_TYPE type = RESOURCE_TYPE::UNKNOWN;
	uint loaded = 0;
};

#endif
