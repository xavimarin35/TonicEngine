#include "ComponentButton.h"
#include "ButtonUI.h"

ComponentButton::ComponentButton(GameObject* parent) : Component(COMPONENT_TYPE::BUTTON_UI, parent)
{
	type = COMPONENT_TYPE::BUTTON_UI;
	object = parent;

	hover_color = { 0.9f, 0.9f, 0.9f };
	pressed_color = { 0.7f, 0.7f, 0.7f };
}

ComponentButton::~ComponentButton()
{
}

bool ComponentButton::Start()
{
	button = new ButtonUI(this);

	return true;
}

bool ComponentButton::Update()
{
	button->Update();

	return true;
}

bool ComponentButton::CleanUp()
{
	return true;
}

void ComponentButton::Draw()
{
}
