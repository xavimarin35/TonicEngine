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

	GLuint GetCharacterTexture(GLchar character);
	FontCharacterUI* GetCharacterFont(GLchar character);

	std::string name;
	FT_Face text_font;
	std::map<GLchar, FontCharacterUI*> charactersList;
	bool loaded = false;

};

#endif
