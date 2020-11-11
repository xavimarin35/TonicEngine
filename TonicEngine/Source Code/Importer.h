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

	// Export Mesh and Transform
	bool Export(const char* path, std::string& file, ComponentMesh* mesh);
	bool Export(const char* path, std::string& file, ComponentTransform* transform);

	// Load Mesh and Transform
	bool Load(const char* path, ComponentMesh* mesh);
	bool Load(const char* path, ComponentTransform* transform);

};

#endif