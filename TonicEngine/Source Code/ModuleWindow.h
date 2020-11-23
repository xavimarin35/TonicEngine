#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);
	const char* GetTitle();

	// Window SDL functions
	void GetWindowSize(int width, int height);
	int GetWidth();
	int GetHeight();
	void SetFullScreen(bool active);
	void SetResizable(bool active);
	void SetBorderless(bool active);

public:
	//The window we'll be rendering to
	SDL_Window* window;

	//The surface contained by the window
	SDL_Surface* screen_surface;
};

#endif // __ModuleWindow_H__