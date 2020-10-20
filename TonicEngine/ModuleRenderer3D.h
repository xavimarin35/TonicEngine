#ifndef __ModuleRenderer3D__
#define __ModuleRenderer3D__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#define MAX_LIGHTS 8

class MeshObj;

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

	void NewVertexBuffer(float* vertex, uint& size, uint& id_vertex);
	void NewIndexBuffer(uint* index, uint& size, uint& id_index);
	void Draw(const MeshObj* mesh);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
};

#endif __ModuleRenderer3D__