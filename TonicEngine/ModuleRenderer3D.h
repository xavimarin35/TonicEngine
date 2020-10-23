#pragma once
#include "Module.h"
#include "Globals.h"
#include "Math.h"
#include "Light.h"
#include "ModuleImporter.h"

#define MAX_LIGHTS 8

struct MeshObj;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void NewVertexBuffer(float3* vertex, uint& size, uint& id_vertex);
	void NewIndexBuffer(uint* index, uint& size, uint& id_index);
	void NewTextBuffer(float* text_coords, uint& num_text_coords, uint& id_text_coords);
	void DrawObj(const MeshObj* mesh);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

};