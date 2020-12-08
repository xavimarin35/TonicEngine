#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include "Module.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"

class ResourceMesh;

struct meshData;

class Importer 
{
public:
	Importer();
	~Importer();

public:

	bool Export(const char* path, std::string& file, ComponentMesh* mesh);

};

#endif