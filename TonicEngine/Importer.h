#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include "Globals.h"
#include <string>

class Texture;

class Importer 
{
public:
	Importer();
	~Importer();

public:

	bool Import(const char* filename, const char* path, std::string& file);
	bool Import(const void* buffer, uint size, std::string& file);

	bool Load(const char* file, Texture* texture);
	bool LoadCheckers(Texture* texture);
};

#endif