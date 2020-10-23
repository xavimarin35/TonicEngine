#ifndef __TEXTURE_IMPORTER_H__
#define __TEXTURE_IMPORTER_H__

#include "Globals.h"
#include "Module.h"

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

	uint CreateTexture(const void* texture, uint width, uint height, int format, uint format2) const;
	uint CreateCheckersText(uint width, uint height) const;
	uint LoadTexture(const char* path) const;

	uint id_checkers = 0;
};

#endif