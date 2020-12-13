#include "Resource.h"
#include "Application.h"

RESOURCE_TYPE Resource::GetType() const
{
	return type;
}

uint Resource::GetUUID() const
{
	return res_UUID;
}

uint Resource::GetCurrentReference()
{
	return references;
}