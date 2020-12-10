#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "MeshImporter.h"
#include "ModuleResources.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG_C("Loading Input");
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for(int i = 0; i < 5; ++i)
	{
		if(buttons & SDL_BUTTON(i))
		{
			if(mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		App->gui->EnableInput(&e);

		switch(e.type)
		{
			case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_QUIT:
			/*quit = true;*/
			App->gui->exitMenu = true;
			break;

			case SDL_WINDOWEVENT:
			{
				if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					App->renderer3D->OnResize(e.window.data1, e.window.data2);
				break;
			}

			// File Dropped on scene
			case SDL_DROPFILE:
			{
				dropDirection = e.drop.file;

				// FBX or OBJ
				if (strstr(dropDirection, ".fbx") != nullptr || strstr(dropDirection, ".FBX") != nullptr || strstr(dropDirection, ".obj") != nullptr || strstr(dropDirection, ".OBJ") != nullptr)
				{
					App->mesh_imp->LoadFile(dropDirection);
					MeshFileDroped = true;
					LOG_C("New file dropped on window with path: %s", dropDirection);
				}

				// PNG or DDS
				else if (strstr(dropDirection, ".png") != nullptr || strstr(dropDirection, ".dds") != nullptr || strstr(dropDirection, ".tga") != nullptr)
				{
					if (App->scene_intro->GOselected != nullptr)
					{
						if (App->scene_intro->GOselected->GetComponentTexture() == nullptr)
						{
							LOG_C("WARNING: This Game Object doesn't have a Component Texture, maybe try with another child");
						}
						else
						{
							App->scene_intro->GOselected->GetComponentTexture()->rTexture = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile(dropDirection));
							App->scene_intro->GOselected->GetComponentTexture()->rTexture->LoadInMemory();
							//App->tex_imp->LoadTexture(dropDirection);
							TextureFileDropped = true;
							LOG_C("New texture dropped on window with path: %s", dropDirection);
						}
					}
					else
					{
						LOG_C("ERROR: You must select a GameObject to drop a texture!");
					}
					
				}
				else
					LOG_C("ERROR: File dropped extension not supported! Try '.fbx', '.obj', '.png' or 'dds'");

				SDL_free((char*)dropDirection);
				break;
			}
		}
	}

	if (/*quit == true ||*/ keyboard[SDL_SCANCODE_LALT] == KEY_REPEAT && keyboard[SDL_SCANCODE_F4] == KEY_DOWN)
		App->quitApp = true;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
