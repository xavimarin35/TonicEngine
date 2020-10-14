#pragma once
#include "Globals.h"
#include "Application.h"

class aiMesh;

class MeshObj
{

public:

	MeshObj();
	~MeshObj();

	bool Load(aiMesh* mesh2);

	void CleanUp();

public:

	uint id_index = 0;
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0;
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint num_normals = 0;
	float* normals = nullptr;

	uint id_color = 0;
	uint num_color = 0;
	float* colors = nullptr;
};