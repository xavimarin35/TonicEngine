#ifndef _FONTCHARACTER_UI_H_
#define _FONTCHARACTER_UI_H_

#include "ModuleUserInterface.h"
#include "imgui-1.78/imgui.h"
#include "glew/include/GL/glew.h"

class FontCharacterUI
{
public:
	FontCharacterUI();
	FontCharacterUI(GLuint id, float2 _size, float2 _bearing, GLuint _advance);
	~FontCharacterUI();

	GLuint     TextureID;  // ID handle of the glyph texture
	float2     Size;       // Size of glyph
	float2     Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

#endif