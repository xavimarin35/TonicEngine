#include "TextureImporter.h"
#include "Application.h"

#include "glew/include/GL/glew.h"

#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

#pragma comment ( lib, "DevIL/libx86/DevIL.lib" )
#pragma comment ( lib, "DevIL/libx86/ILU.lib" )
#pragma comment ( lib, "DevIL/libx86/ILUT.lib" )

#define CHECKERS_WIDTH 16
#define CHECKERS_HEIGHT 16

TextureImporter::TextureImporter(Application* app, bool start_enabled) : Module(app, start_enabled) { }
TextureImporter::~TextureImporter() { }

bool TextureImporter::Init()
{
	bool ret = true;

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || iluGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		App->appLogs.push_back("DevIL version not correct");
		ret = false;
	}

	else
	{
		App->appLogs.push_back("DevIL initializing...");

		ilInit();
		iluInit();
		ilutInit();

		ilutRenderer(ILUT_OPENGL);
	}

	return ret;
}

bool TextureImporter::Start()
{
	id_checkers = CreateCheckersText(CHECKERS_WIDTH, CHECKERS_HEIGHT);

	return true;
}

update_status TextureImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool TextureImporter::CleanUp()
{
	return true;
}

uint TextureImporter::CreateCheckersText(uint width, uint height) const
{
	GLubyte checkImage[CHECKERS_WIDTH][CHECKERS_HEIGHT][4];

	for (int i = 0; i < CHECKERS_WIDTH; i++)
	{
		for (int j = 0; j < CHECKERS_HEIGHT; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;

			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	GLuint texture = 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}