#include "FontUI.h"

FontUI::FontUI()
{
	name = "";
}

FontUI::~FontUI()
{
}

void FontUI::CreateCharacterText()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		FontCharacterUI* new_character = new FontCharacterUI();

		// Load character glyph 
		if (FT_Load_Char(text_font, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		// Generate texture
		glGenTextures(1, &new_character->TextureID);
		glBindTexture(GL_TEXTURE_2D, new_character->TextureID);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			text_font->glyph->bitmap.width,
			text_font->glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			text_font->glyph->bitmap.buffer
		);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		new_character->Bearing = { (float)text_font->glyph->bitmap.width, (float)text_font->glyph->bitmap.rows };
		new_character->Size = { (float)text_font->glyph->bitmap_left, (float)text_font->glyph->bitmap_top };
		new_character->Advance = text_font->glyph->advance.x;

		charactersList.insert(std::pair<GLchar, FontCharacterUI*>(c, new_character));
		loaded = true;
	}
}

GLuint FontUI::GetCharacterTexture(GLchar character)
{
	for (std::map<GLchar, FontCharacterUI*>::const_iterator it = charactersList.begin(); it != charactersList.end(); it++)
	{
		if ((*it).first == character)
		{
			GLuint id = (*it).second->TextureID;
			return id;
		}
	}

	return GLuint();
}

FontCharacterUI* FontUI::GetCharacterFont(GLchar character)
{
	for (std::map<GLchar, FontCharacterUI*>::const_iterator it = charactersList.begin(); it != charactersList.end(); it++)
	{
		if ((*it).first == character)
		{
			return (*it).second;
		}
	}

	return nullptr;
}
