#ifndef __TEXTURE_IMPORTER_H__
#define __TEXTURE_IMPORTER_H__

#include "Globals.h"
#include "Module.h"

struct Texture
{
	uint id, height, width;
	std::string path;
};

class TextureImporter : public Module
{
public:

	TextureImporter(Application* app, bool start_enabled = true);
	~TextureImporter();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	bool DuplicateTexture(const char* path) const;

public:

	uint CreateTexture(const void* texture, const char* path, uint width, uint height, int format, uint format2) const;
	Texture CreateEmptyTexture() const;

	Texture LoadTexture(const char* path) const;
	Texture GenerateCheckersTexture();

	Texture texture;
	Texture checker_texture;

};

#endif