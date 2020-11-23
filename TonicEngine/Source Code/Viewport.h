#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "Application.h"
#include "PanelManager.h"
#include "TextureImporter.h"
#include "ComponentCamera.h"

class Viewport
{
public:
	Viewport();
	~Viewport();

	bool Start();
	bool PreUpdate();
	bool PostUpdate();
	bool CleanUp();

	void ChooseCamera(ComponentCamera* camera);
	void PrintTexture(uint tex);

public:

};


#endif
