#include "Importer.h"

Importer::Importer()
{
}

Importer::~Importer()
{
}

bool Importer::Import(const char* file, const char* path, std::string& output_file)
{
	return false;
}

bool Importer::Import(const void* buffer, uint size, std::string& output_file)
{
	return false;
}

bool Importer::Load(const char* exported_file, Texture* resource)
{
	return false;
}

bool Importer::LoadCheckers(Texture* resource)
{
	return false;
}