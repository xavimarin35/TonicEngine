#ifndef _FONT_UI_H_
#define _FONT_UI_H_

#include "ModuleUserInterface.h"
#include "imgui-1.78/imgui.h"
#include "glew/include/GL/glew.h"
#include "FontCharacterUI.h"

class FontUI
{
public:
	FontUI();
	~FontUI();

	void CreateCharacterText();

	std::string name;
	FT_Face text_font;
	std::map<GLchar, FontCharacterUI*> chars_list;
	bool loaded = false;

};

#endif
