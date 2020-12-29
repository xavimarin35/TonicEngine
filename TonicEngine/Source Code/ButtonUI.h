#ifndef _BUTTON_UI_H_
#define _BUTTON_UI_H_

#include "ElementUI.h"

class ComponentButton;

class ButtonUI : public ElementUI
{
public:
	ButtonUI(ComponentButton* button);
	~ButtonUI();

	bool Start();
	bool Update();
	bool CleanUp();
	bool Draw();

	ComponentButton* Cbutton;

private:


};

#endif
