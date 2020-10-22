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

	uint LoadImage() const;
	uint CreateTexture(const char* path) const;
	uint CreateCheckersText(uint width, uint height) const;
	uint GetCheckerText() const;

	uint id_checkers = 0;
};

#endif