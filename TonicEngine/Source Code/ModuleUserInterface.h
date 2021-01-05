#ifndef _MODULE_USERINTERFACE_H_
#define _MODULE_USERINTERFACE_H_

#include "Module.h"
#include "GameObject.h"
#include <list>

#include <ft2build.h>
#include FT_FREETYPE_H

#pragma comment(lib, "FreeType/libx86/freetype.lib") 

class FontUI;

class ModuleUserInterface : public Module
{
public:
	ModuleUserInterface(Application* app, bool start_enabled = true);
	~ModuleUserInterface();

	bool Init();
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	FontUI* LoadFont(std::string name, int size);
	FontUI* GetFont(std::string name);
	void SetOrthogonalCamera();
	void SetUIRenderSettings();
	void DrawUI();
	void AddCanvasGO(GameObject* GO);

private:

	FT_Library ft_library = FT_Library();
	std::list<FontUI*> fontsList;
	std::vector<GameObject*> GOcanvas;
};

#endif
