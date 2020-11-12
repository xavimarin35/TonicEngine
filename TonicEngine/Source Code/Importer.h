#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include "Module.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"

struct meshData;

class Importer 
{
public:
	Importer();
	~Importer();

public:

	// Export Mesh
	bool Export(const char* path, std::string& file, ComponentMesh* mesh);


};

#endif