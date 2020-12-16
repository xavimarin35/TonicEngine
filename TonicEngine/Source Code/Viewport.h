#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "Application.h"
#include "Globals.h"
#include "glew/include/GL/glew.h"
#include "imgui-1.78/imgui.h"

class Viewport
{
public:
	Viewport();
	~Viewport();

	bool Create(int width, int height);
	void BindViewport();
	void UnbindViewport();
	bool CleanUp();

	void DeleteBuffers();
	GLuint GetTexture();

	int GetViewportWidth();
	int GetViewportHeight();

	void SetViewportWidth(int w);
	void SetViewportHeight(int h);


public:

	GLuint fbo;
	GLuint rbo;
	GLuint texture;

	int width = 0;
	int height = 0;
};

#endif