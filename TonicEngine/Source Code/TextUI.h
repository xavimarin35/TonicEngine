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

	void CreateTextContainer(GLchar character, float3 position); // Dont know if it has to be GLchar or const char* and if the position parameter can be removed in a future
	void FillTextArray();

	std::string GetText();
	void SetText(std::string new_text);
	void SetFont(string name);

	ComponentText* Ctext = nullptr;

	char inspector_text[100];

private:

	std::string current_text;
	FontUI* current_font = nullptr;

	std::list<ImageUI*> textList;

};

#endif
