#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 ) // Warning that exceptions are disabled

#include <windows.h>
#include <stdio.h>

using namespace std;

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI


#define IM_NEWLINE "\r\n"

// PCG (Random Number Generator) functions
void InitSeed();
float GenerateRandomFloat();
int GenerateRandomInt();
int GenerateRandomBetween(int bound);

typedef unsigned int uint;

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Deletes a buffer
#define RELEASE( x )\
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x )\
	{\
       if( x != nullptr )\
       {\
           delete[] x;\
	       x = nullptr;\
		 }\
    }

// JSON assert 
#include <cassert>
#define JSON_ASSERT(x) assert(x)

// Configuration -----------
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SCREEN_SIZE 1
#define WIN_MAXIMIZED true
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true

//Common Directories
#define ASSETS_FOLDER "/Assets/"
#define ASSETS_SCENES_FOLDER "Assets/Scenes/" // It must not have a / before Assets, even though it won't create any .json file
#define ASSETS_TEXTURES_FOLDER "Assets/Textures/"
#define ASSETS_MODELS_FOLDER "Assets/Models/"
#define LIBRARY_FOLDER "/Library/"
#define LIBRARY_TEXTURES_FOLDER "/Library/Textures/"
#define LIBRARY_MESH_FOLDER "/Library/Meshes/"