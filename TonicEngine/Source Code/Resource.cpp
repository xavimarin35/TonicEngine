#include "Resource.h"
#include "Application.h"

RESOURCE_TYPE Resource::GetType() const
{
	return type;
}

bool Resource::IsLoadedToMemory() const
{
	return true;
}

bool Resource::LoadToMemory()
{
	return true;
}

uint Resource::GetUUID() const
{
	return res_UUID;
}

const char* Resource::GetFile() const
{
	return nullptr;
}

const char* Resource::GetImportedFile() const
{
	return nullptr;
}

void Resource::UpdateReferences()
{
	if (loaded > 0)
		loaded++;
	else
	{
		if (LoadInMemory())
			loaded = 1;
		else
			loaded = 0;
	}
}

uint Resource::GetCurrentReference()
{
	return loaded;
}

void Resource::Load(const nlohmann::json& config)
{
}

void Resource::Save(nlohmann::json& config) const
{
}
