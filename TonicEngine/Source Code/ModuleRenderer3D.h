#ifndef __ModuleRenderer3D__
#define __ModuleRenderer3D__

#include "Application.h"
#include "Light.h"
#include "GameObject.h"

#define MAX_LIGHTS 8

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

	void VertexBuffer(float3* vertex, uint& size, uint& id_vertex);
	void IndexBuffer(uint* index, uint& size, uint& id_index);
	void TextureBuffer(float* text_coords, uint& num_text_coords, uint& id_text_coords);
	void DeleteBuffer(uint& type);

	void GenerateObject(GameObject* GO);
	float* GetProjectionMatrix();

	// View Mode
	void WireframeView(bool active);
	void DepthView(bool active);
	void CullFaceView(bool active);
	void LightingView(bool active);
	void AlphaView(bool active);
	void Texture2DView(bool active);

public:
	

	ComponentCamera* culling = nullptr;

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	Color bg_color = { 0.f, 0.f, 0.05f };

};

#endif 