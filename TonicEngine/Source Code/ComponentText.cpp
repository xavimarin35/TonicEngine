#include "ComponentText.h"
#include "TextUI.h"

ComponentText::ComponentText(GameObject* parent) : Component(COMPONENT_TYPE::TEXT_UI, parent)
{
	type = COMPONENT_TYPE::TEXT_UI;
	object = parent;

	text = new TextUI(this);
}

ComponentText::~ComponentText()
{
}

bool ComponentText::Start()
{
	return true;
}

bool ComponentText::Update()
{
	return true;
}

bool ComponentText::CleanUp()
{
	return true;
}

void ComponentText::Draw()
{
	text->Draw();
}

void ComponentText::DrawInspector()
{
}
