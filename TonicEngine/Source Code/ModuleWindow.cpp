#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleGUI.h"
#include "ModuleRenderer3D.h"

#include "glew/include/GL/glew.h"
#include "SDL/include/SDL.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG_C("Init SDL window & surface");
	LOG_C("Loading Window");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 3.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if (WIN_MAXIMIZED == true)
		{
			flags |= SDL_WINDOW_MAXIMIZED;
		}

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(App->appName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

const char* ModuleWindow::GetTitle()
{
	const char* name;
	name = SDL_GetWindowTitle(window);

	return name;
}

void ModuleWindow::GetWindowSize(int width, int height)
{
	SDL_GetWindowSize(window, &width, &height);
}

int ModuleWindow::GetWidth()
{
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	return width;
}

int ModuleWindow::GetHeight()
{
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	return height;
}

void ModuleWindow::SetFullScreen(bool active)
{
	if (active)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else
		SDL_SetWindowFullscreen(window, SDL_WINDOW_MINIMIZED);
}

void ModuleWindow::SetResizable(bool active)
{
	if (active)
		SDL_SetWindowResizable(window, SDL_TRUE);
	else
		SDL_SetWindowResizable(window, SDL_FALSE);
}

void ModuleWindow::SetBorderless(bool active)
{
	if (active)
		SDL_SetWindowBordered(window, SDL_FALSE);
	else
		SDL_SetWindowBordered(window, SDL_TRUE);
}

