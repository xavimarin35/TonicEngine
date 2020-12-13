#ifndef __TEXTURE_IMPORTER_H__
#define __TEXTURE_IMPORTER_H__

#include "Globals.h"
#include "Module.h"

class ResourceTexture;

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

public:

	uint CreateTexture(const void* texture, uint width, uint height, int format, uint format2, const char* path = nullptr) const;
	Texture CreateEmptyTexture() const;

	bool LoadTextureFromPath(const char* path, std::string& output_file);
	Texture GenerateCheckersTexture();
	bool LoadTextureFromLibrary(ResourceTexture* tex);

	bool DuplicateTexture(const char* path, std::string& output_file) const;

	// Textures used for opengl purposes
	Texture texture;
	Texture checker_texture;
};

#endif