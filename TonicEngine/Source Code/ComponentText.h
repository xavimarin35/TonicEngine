#ifndef _COMPONENT_TEXT_H_
#define _COMPONENT_TEXT_H_

#include "Component.h"

class ElementUI;
class TextUI;

class ComponentText : public Component
{
public:

	ComponentText(GameObject* parent);
	~ComponentText();

	bool Start();
	bool Update();
	bool CleanUp();
	void Draw();
	void DrawInspector();

private:

	TextUI* text = nullptr;

};

#endif
