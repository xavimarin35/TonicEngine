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

	bool StartBuffers(ImVec2 size);
	void BindViewport();
	void UnbindViewport();
	bool CleanUp();

	void DeleteBuffers();
	GLuint GetTexture();

public:

	GLuint fbo;
	GLuint rbo;
	GLuint texture;
};

#endif