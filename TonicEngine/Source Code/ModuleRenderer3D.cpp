#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "MeshImporter.h"
#include "ModuleWindow.h"
#include "ModuleSceneIntro.h"
#include "ModuleGUI.h"
#include "ModuleCamera3D.h"
#include "GameObject.h"
#include "Viewport.h"
#include "ModuleWindow.h"

#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG_C("Loading 3D Renderer Context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		ret = false;
	}

	if(ret == true)
	{
		glewInit();

		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG_C("ERROR: Unable to set VSync");

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		lights[0].Active(true);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
	}

	//OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderPanelTexture(PANEL_TEXTURE::SCENE, SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderPanelTexture(PANEL_TEXTURE::GAME, SCREEN_WIDTH, SCREEN_HEIGHT);

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	//Environment Color
	glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.f);

	// In playmode projection
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glLoadMatrixf((GLfloat*)App->camera->GetProjection());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

	// Rendering Scene in Scene Panel ---------------
	glBindFramebuffer(GL_FRAMEBUFFER, scene_fbo);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetView());

	// Draw objects and axis
	App->scene_intro->PostUpdate(dt);
	
	// Debug Draw of Bounding Boxes
	for (std::vector<GameObject*>::iterator it = App->scene_intro->gameobjectsList.begin(); it != App->scene_intro->gameobjectsList.end(); ++it)
	{
		(*it)->Update();
	}

	// Debug Draw of Camera Frustum
	for (std::vector<GameObject*>::iterator it = App->scene_intro->gameobjectsList.begin(); it != App->scene_intro->gameobjectsList.end(); ++it)
	{
		if ((*it)->GetComponentCamera() != nullptr)
			(*it)->GetComponentCamera()->Update();
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// -------------

	// Rendering Game in Game Panel --------------------
	glBindFramebuffer(GL_FRAMEBUFFER, game_fbo);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (App->camera->playCam != nullptr)
	{
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(App->camera->GetGameView());

		// Draw objects and axis
		App->scene_intro->PostUpdate(dt);
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// -------------

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();


	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::PostUpdate(float dt)
{
	ComponentCamera* cam = culling;

	if (culling == nullptr)
		cam = App->camera->GetActiveCamera();
	else cam->DrawCamera();

	std::vector<const GameObject*> objs;

	GO::Culling(objs, App->scene_intro->GOroot);

	for (int i = 0; i < objs.size(); i++)
	{
		if (objs[i]->data.active && cam->Intersect(objs[i]->aabb))
		{
			objs[i]->Draw();
		}
	}

	// Drawing Panels
	App->gui->Draw();

	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRenderer3D::OnResize(int width, int height)
{
	/*glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);*/
}

void ModuleRenderer3D::RenderPanelTexture(PANEL_TEXTURE panel_tex, int width, int height) // This function also includes the OnResize() function
{
	if (panel_tex == PANEL_TEXTURE::SCENE)
	{
		glDeleteFramebuffers(1, &scene_fbo);
		glDeleteTextures(1, &scene_tex);
		glDeleteRenderbuffers(1, &scene_depth);

		glGenFramebuffers(1, &scene_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, scene_fbo);

		glGenTextures(1, &scene_tex);

		glBindTexture(GL_TEXTURE_2D, scene_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glGenRenderbuffers(1, &scene_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, scene_depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, scene_depth);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, scene_tex, 0);
	}

	if (panel_tex == PANEL_TEXTURE::GAME)
	{
		glDeleteFramebuffers(1, &game_fbo);
		glDeleteTextures(1, &game_tex);
		glDeleteRenderbuffers(1, &game_depth);

		glGenFramebuffers(1, &game_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, game_fbo);

		glGenTextures(1, &game_tex);

		glBindTexture(GL_TEXTURE_2D, game_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glGenRenderbuffers(1, &game_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, game_depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, game_depth);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, game_tex, 0);
	}

	// OnResize() -----------
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);
	// ----------------------

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void ModuleRenderer3D::VertexBuffer(float3* vertex, uint& size, uint& id_vertex)
{
	glGenBuffers(1, (GLuint*) &(id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float3) * size, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleRenderer3D::IndexBuffer(uint* index, uint& size, uint& id_index)
{
	glGenBuffers(1, (GLuint*) &(id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * size, index, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleRenderer3D::TextureBuffer(float* text_coords, uint& num_text_coords, uint& id_text_coords)
{
	glGenBuffers(1, (GLuint*) &(id_text_coords));
	glBindBuffer(GL_ARRAY_BUFFER, id_text_coords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_text_coords * 2, text_coords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModuleRenderer3D::DeleteBuffer(uint& type)
{
	glDeleteBuffers(1, &(GLuint)type);
}

void ModuleRenderer3D::GenerateObject(GameObject* GO)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (GO->GetComponentTexture() != nullptr)
	{
		if (GO->GetComponentTexture()->active && GO->GetComponentTexture()->rTexture != nullptr)
		{
			if (GO->GetComponentTexture()->EnableAssignedTexture)
				glBindTexture(GL_TEXTURE_2D, GO->GetComponentTexture()->rTexture->tex.id);
			else if (GO->GetComponentTexture()->EnableCheckersTexture)
				glBindTexture(GL_TEXTURE_2D, App->tex_imp->checker_texture.id);
		}
		else
			glBindTexture(GL_TEXTURE_2D, NULL);
	}

	if (GO->GetComponentMesh() != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, GO->GetComponentMesh()->rMesh->data.id_vertex);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glActiveTexture(GL_TEXTURE0);

		glBindBuffer(GL_ARRAY_BUFFER, GO->GetComponentMesh()->rMesh->data.id_tex_coords);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GO->GetComponentMesh()->rMesh->data.id_index);
		glDrawElements(GL_TRIANGLES, GO->GetComponentMesh()->rMesh->data.num_index, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisableClientState(GL_VERTEX_ARRAY);

	}
}

// ImGuizmo purposes
float* ModuleRenderer3D::GetProjectionMatrix()
{
	return &ProjectionMatrix;
}

// View Modes
void ModuleRenderer3D::WireframeView(bool active)
{
	if (active)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ModuleRenderer3D::DepthView(bool active)
{
	if (active)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void ModuleRenderer3D::CullFaceView(bool active)
{
	if (active)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void ModuleRenderer3D::LightingView(bool active)
{
	if (active)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);
}

void ModuleRenderer3D::AlphaView(bool active)
{
	if (active)
		glEnable(GL_BLEND);

	else
		glDisable(GL_BLEND);
}

void ModuleRenderer3D::Texture2DView(bool active)
{
	if (active)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
}