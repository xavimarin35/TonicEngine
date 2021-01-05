#include "TextUI.h"
#include "ImageUI.h"
#include "ContainerUI.h"

TextUI::TextUI(ComponentText* text)
{
	Ctext = text;
	SetFont("arial");
	SetText("ansu papi");
}

TextUI::~TextUI()
{
}

bool TextUI::Start()
{
	return true;
}

bool TextUI::Update()
{
	return true;
}

bool TextUI::CleanUp()
{
	return true;
}

bool TextUI::Draw()
{
	return true;
}

void TextUI::CreateTextContainer(GLchar character, float3 position) // Dont know if it has to be GLchar or const char* and if the position parameter can be removed in a future
{
	// Set proper size
	FT_Load_Char(current_font->text_font, (GLchar)character, FT_LOAD_RENDER);
	ImVec2 size = { (float)current_font->text_font->glyph->bitmap.width, (float)current_font->text_font->glyph->bitmap.rows };

	// Create the corresponding container 
	ImageUI* char_img = new ImageUI(nullptr);
	//char_img->GetContainer()->InvertImage(size);

	// Get the corresponding texture 
	uint texture_id = current_font->GetCharacterTexture(character);
	char_img->SetImageID(texture_id);

	textList.push_back(char_img);
}

void TextUI::FillTextArray()
{
	for (int i = 0; i < current_text.size(); i++)
	{
		CreateTextContainer((GLchar)current_text[i], { 0,0,0 }); // Dont know if it has to be GLchar or const char* and if the position parameter can be removed in a future
	}
}

std::string TextUI::GetText()
{
	return current_text;
}

void TextUI::SetText(std::string new_text)
{
	current_text = new_text;
	textList.clear();
	FillTextArray();
}

void TextUI::SetFont(string name)
{
	current_font = App->ui->GetFont(name);
}
