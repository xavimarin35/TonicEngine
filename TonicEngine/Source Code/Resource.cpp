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

uint Resource::GetCurrentReference()
{
	return references;
}

