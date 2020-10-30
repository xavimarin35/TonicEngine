#include "TextureImporter.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"

#include "glew/include/GL/glew.h"

#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

#pragma comment ( lib, "DevIL/libx86/DevIL.lib" )
#pragma comment ( lib, "DevIL/libx86/ILU.lib" )
#pragma comment ( lib, "DevIL/libx86/ILUT.lib" )

TextureImporter::TextureImporter(Application* app, bool start_enabled) : Module(app, start_enabled) { }
TextureImporter::~TextureImporter() { }

bool TextureImporter::Init()
{
	bool ret = true;

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || iluGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		LOG_IMGUI_CONSOLE("ERROR: DevIL version not correct");
		ret = false;
	}

	else
	{
		LOG_IMGUI_CONSOLE("Initializing DevIL");

		ilInit();
		iluInit();
		ilutInit();

		ilutRenderer(ILUT_OPENGL);
	}

	return ret;
}

bool TextureImporter::Start()
{

	return true;
}

update_status TextureImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool TextureImporter::CleanUp()
{
	glDeleteTextures(1, (GLuint*)&checker_texture);

	return true;
}


uint TextureImporter::CreateEmptyTexture() const
{
	uint  texture;

	return texture;
}

uint TextureImporter::CreateTexture(const void* text, const char* path, uint width, uint height, int format, uint format2) const
{
	uint tex = 0;

	glGenTextures(1, (GLuint*)&tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, text);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind Texture
	glBindTexture(GL_TEXTURE_2D, 0);


	LOG_IMGUI_CONSOLE("Loaded Texture(% i x % i) with path: %s", width, height, path);
	

	return tex;
}

uint TextureImporter::GenerateTexture(const char* path)
{
	ILuint pic;
	uint t;
	uint info;
	
	if (path != nullptr)
	{
		ilGenImages(1, (GLuint*)&info);
		ilBindImage(info);

		if (ilLoadImage(path)) {

			t = ilutGLBindTexImage();

			if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
				t = CreateTexture(ilGetData(), path, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_FORMAT));
			
			if (App->scene_intro->GOselected != nullptr)
			{
				App->scene_intro->GOselected->GetComponentTexture()->texture_path = path;
			}

			return t;
		}
		else
		{
			ilDeleteImages(1, &pic);
			return 0;
		}
	}

	
}

void TextureImporter::GenerateCheckersTexture()
{
	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

	for (int i = 0; i < CHECKERS_HEIGHT; i++)
	{
		for (int j = 0; j < CHECKERS_WIDTH; j++)
		{
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &checker_texture);
	glBindTexture(GL_TEXTURE_2D, checker_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	glBindTexture(GL_TEXTURE_2D, 0);
}
