#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include "Module.h"
#include "ComponentMesh.h"

struct meshData;

class Importer 
{
public:
	Importer();
	~Importer();

public:

	bool Import(const char* path, std::string& file, ComponentMesh* mesh);
};

#endif