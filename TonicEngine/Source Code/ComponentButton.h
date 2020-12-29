#ifndef _COMPONENT_BUTTON_H_
#define _COMPONENT_BUTTON_H_

#include "Component.h"
#include "Math.h"
#include "SDL\include\SDL_rect.h"

#include <list>
#include <string>

class ElementUI;
class ButtonUI;
class GameObject;

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

private:

	ButtonUI* button = nullptr;

	float3 hover_color = { 0,0,0 };
	float3 pressed_color = { 0,0,0 };

};

#endif
