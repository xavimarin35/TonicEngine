#ifndef _TEXT_UI_H_
#define _TEXT_UI_H_

#include "ElementUI.h"
#include "ModuleUserInterface.h"
#include "FontUI.h"

class ComponentText;
class ImageUI;

class TextUI : public ElementUI
{
public:
	TextUI(ComponentText* text);
	~TextUI();

	bool Start();
	bool Update();
	bool CleanUp();
	bool Draw();

	void CreateTextContainer(const char* character, float3 position);
	void FillTextArray();

	ComponentText* Ctext = nullptr;

private:

	std::string current_text;
	FontUI current_font;
	int text_size;

	std::list<ImageUI*> text_images;

};

#endif
