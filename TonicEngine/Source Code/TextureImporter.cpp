#include "TextureImporter.h"
#include "Application.h"
#include "ModuleGUI.h"
#include "ModuleSceneIntro.h"
#include "ModuleFileSystem.h"

#include "glew/include/GL/glew.h"

#include "DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include "DevIL/include/IL/ilut.h"

#pragma comment ( lib, "DevIL/libx86/DevIL.lib" )
#pragma comment ( lib, "DevIL/libx86/ILU.lib" )
#pragma comment ( lib, "DevIL/libx86/ILUT.lib" )

#define CHECKERS_WIDTH 128
#define CHECKERS_HEIGHT 128

TextureImporter::TextureImporter(Application* app, bool start_enabled) : Module(app, start_enabled) { }
TextureImporter::~TextureImporter() { }

bool TextureImporter::Init()
{
	bool ret = true;

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || iluGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		LOG_C("ERROR: DevIL version not correct");
		ret = false;
	}

	else
	{
		LOG_C("Initializing DevIL");

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
	glDeleteTextures(1, (GLuint*)&texture);

	return true;
}

bool TextureImporter::DuplicateTexture(const char* path) const
{
	bool ret = false;
	
	std::string name = App->GetPathName(path);
	std::string output_file;

	ILuint size;
	ILubyte* data;

	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);
	size = ilSaveL(IL_DDS, NULL, 0);

	if (size > 0)
	{
		data = new ILubyte[size];

		if (ilSaveL(IL_DDS, data, size) > 0)
			ret = App->file_system->SaveUnique(output_file, data, size, LIBRARY_TEXTURES_FOLDER, name.data(), "Ttext");

		LOG_C("NICE: Correctly exported %s.Ttext into Textures folder", path);

		RELEASE_ARRAY(data);
	}

	return ret;
}

Texture TextureImporter::CreateEmptyTexture() const
{
	Texture tex;
	tex.id = 0;
	tex.width = 0;
	tex.height = 0;
	tex.path = "none";

	return tex;
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

	if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
	{
		float max_anisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format2, GL_UNSIGNED_BYTE, text);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//int actualGO = App->scene_intro->gameobjectsList.size() - 1;
	//App->scene_intro->gameobjectsList[actualGO]->textureWidth = width;
	//App->scene_intro->gameobjectsList[actualGO]->textureHeight = height;

	LOG_C("Loaded Texture(%i x %i) with path: %s", width, height, path);

	return tex;
}

Texture TextureImporter::GenerateCheckersTexture()
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

	Texture tex;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &tex.id);
	glBindTexture(GL_TEXTURE_2D, tex.id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	tex.height = CHECKERS_HEIGHT;
	tex.width = CHECKERS_WIDTH;
	tex.path = "None";

	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}

Texture TextureImporter::LoadTexture(const char* path) const
{
	Texture tex;
	uint id_img = 0;

	if (path != nullptr)
	{
		ilGenImages(1, (ILuint*)&id_img);
		ilBindImage(id_img);

		if (ilLoadImage(path))
		{
			ILinfo info;
			iluGetImageInfo(&info);

			if (info.Origin == IL_ORIGIN_UPPER_LEFT) iluFlipImage();

			if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
			{
				tex.id = CreateTexture(ilGetData(), path, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_FORMAT));
				tex.height = ilGetInteger(IL_IMAGE_HEIGHT);
				tex.width = ilGetInteger(IL_IMAGE_WIDTH);
				tex.path = path;

				DuplicateTexture(path);
			}
			else LOG_C("ERROR: Failed converting image: %s", iluErrorString(ilGetError()));
		}
		else LOG_C("ERROR: Failed loading image: %s", iluErrorString(ilGetError()));
	}
	else LOG_C("ERROR: Failed loading image from path: %s", path);

	return tex;
}