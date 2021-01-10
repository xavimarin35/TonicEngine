#ifndef _COMPONENT_BUTTON_H_
#define _COMPONENT_BUTTON_H_

#include "Component.h"

class ElementUI;
class ButtonUI;

class ComponentButton : public Component
{
public:

	ComponentButton(GameObject* parent);
	~ComponentButton();

	bool Start();
	bool Update();
	bool CleanUp();
	void Draw();
	void DrawInspector();

	int button_function = -1;

private:

	ButtonUI* button = nullptr;

	float3 hover_color = { 0,0,0 };
	float3 pressed_color = { 0,0,0 };

};

#endif
