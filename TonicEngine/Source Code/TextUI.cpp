#include "TextUI.h"

TextUI::TextUI(ComponentText* text)
{
	Ctext = text;

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

void TextUI::CreateTextContainer(const char* character, float3 position)
{
}

void TextUI::FillTextArray()
{
}
