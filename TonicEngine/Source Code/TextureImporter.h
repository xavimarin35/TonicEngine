#ifndef __TEXTURE_IMPORTER_H__
#define __TEXTURE_IMPORTER_H__

#include "Globals.h"
#include "Module.h"

#define CHECKERS_WIDTH 128
#define CHECKERS_HEIGHT 128


class TextureImporter : public Module
{
public:

	TextureImporter(Application* app, bool start_enabled = true);
	~TextureImporter();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	bool DuplicateTexture() const;

public:

	uint CreateTexture(const void* texture, const char* path, uint width, uint height, int format, uint format2);
	uint CreateEmptyTexture() const;

	uint GenerateTexture(const char* path);
	void GenerateCheckersTexture();

	uint texture = 0;
	uint checker_texture = 0;

};

#endif