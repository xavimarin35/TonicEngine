#include "FontCharacterUI.h"

FontCharacterUI::FontCharacterUI()
{
}

FontCharacterUI::FontCharacterUI(GLuint id, float2 _size, float2 _bearing, GLuint _advance)
{
	TextureID = id;
	Size = _size;
	Bearing = _bearing;
	Advance = _advance;
}

FontCharacterUI::~FontCharacterUI()
{
}
